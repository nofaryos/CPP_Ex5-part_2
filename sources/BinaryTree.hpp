#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

namespace ariel{
    template<typename T>
    class BinaryTree{
    private:
        struct Node
        {
            T data;
            Node *left;
            Node *right;
            Node *father;

            Node(const T &value): data(value),left(nullptr), right(nullptr), father(nullptr) {}

        };
    public:
        class preOrder_iterator

        {
        private:

            Node* currentNode;

        public:
            preOrder_iterator(Node* ptr = nullptr): currentNode(ptr){}

            T& operator*() const
            {
                return currentNode->data;
            }

            T* operator->() const
            {
                return &(currentNode->data);
            }
            preOrder_iterator &operator++() {
                if (currentNode == nullptr) {
                    throw std::invalid_argument("Unable to move forward, we have reached the end of the iterator");
                }
                if (currentNode->left != nullptr) { //  left child
                    currentNode = currentNode->left;
                    return *this;
                }
                if (currentNode->right != nullptr) { // right child
                    currentNode = currentNode->right;
                    return *this;
                }
                if (currentNode->father != nullptr && currentNode->father->right != nullptr &&
                        currentNode->father->left == currentNode) {
                    currentNode = currentNode->father->right;
                    return *this;
                }
                if (currentNode->father != nullptr) {
                    while (currentNode == currentNode->father->right && currentNode == currentNode->father->right) {
                        currentNode = currentNode->father;
                        if (currentNode->father == nullptr) {
                            currentNode = nullptr;
                            return *this;
                        }
                    }
                    if (currentNode->father->right != nullptr) {
                        currentNode = currentNode->father->right;
                        return *this;
                    }
                }
                if (currentNode->father != nullptr && currentNode->father->left == currentNode) {
                    while (currentNode->father->right == nullptr || currentNode->father->right == currentNode) {
                        currentNode = currentNode->father;
                        if (currentNode->father == nullptr) {
                            currentNode = nullptr;
                            return *this;
                        }
                    }
                    currentNode = currentNode->father->right;
                    return *this;
                }
                currentNode = nullptr;
                return *this;
            }

            preOrder_iterator operator++(int) {
                preOrder_iterator helpIterator = *this;
                if (currentNode == nullptr) {
                    return helpIterator;
                }
                if (currentNode->left != nullptr) { //  left child
                    currentNode = currentNode->left;
                    return helpIterator;
                }
                if (currentNode->right != nullptr) { // right child
                    currentNode = currentNode->right;
                    return helpIterator;
                }
                if (currentNode->father != nullptr && currentNode->father->right != nullptr &&
                        currentNode->father->left ==
                                currentNode) {
                    currentNode = currentNode->father->right;
                    return helpIterator;
                }
                if (currentNode->father != nullptr && currentNode ==
                                                              currentNode->father->right) {
                    while (currentNode == currentNode->father->right) {
                        currentNode = currentNode->father;
                        if (currentNode->father == nullptr) {
                            currentNode = nullptr;
                            return helpIterator;
                        }
                    }
                    if (currentNode->father->right != nullptr) {
                        currentNode = currentNode->father->right;
                        return helpIterator;
                    }
                }
                if (currentNode->father != nullptr) {
                    while (currentNode->father->right ==
                           nullptr) {
                        currentNode = currentNode->father;
                        if (currentNode->father == nullptr) {
                            currentNode = nullptr;
                            return helpIterator;
                        }
                    }
                    currentNode = currentNode->father->right;
                    return helpIterator;
                }
                currentNode = nullptr;
                return helpIterator;
            }

            bool operator==(const preOrder_iterator& other) const
            {
                return currentNode == other.currentNode;
            }

            bool operator!=(const preOrder_iterator& other) const
            {
                return currentNode != other.currentNode;
            }

        };//End class preOrder_iterator
        class inOrder_iterator
        {
        private:

            Node* currentNode;

        public:
            inOrder_iterator(Node* ptr = nullptr) :currentNode(ptr){}

            T& operator*() const
            {
                return currentNode->data;
            }

            T* operator->() const
            {
                return &(currentNode->data);
            }


            inOrder_iterator &operator++() {
                Node *helpNode = nullptr;
                if (currentNode == nullptr) {
                    throw std::invalid_argument("Unable to move forward, we have reached the end of the iterator");
                }
                if (currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    while (currentNode->left != nullptr) {
                        currentNode = currentNode->left;
                    }
                } else {
                    helpNode = currentNode->father;
                    while (helpNode != nullptr && currentNode == helpNode->right) {
                        currentNode = helpNode;
                        helpNode = helpNode->father;
                    }
                    currentNode = helpNode;
                }
                return *this;
            }


            inOrder_iterator operator++(int) {
                inOrder_iterator helpIterator = *this;
                Node *helpNode = nullptr;
                if (currentNode == nullptr) {
                    return helpIterator;
                }
                if (currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    while (currentNode->left != nullptr) {
                        currentNode = currentNode->left;
                    }
                } else {
                    helpNode = currentNode->father;
                    while (helpNode != nullptr && currentNode == helpNode->right) {
                        currentNode = helpNode;
                        helpNode = helpNode->father;
                    }
                    currentNode = helpNode;
                }
                return helpIterator;
            }

            bool operator==(const inOrder_iterator& other) const
            {
                return currentNode == other.currentNode;
            }
            bool operator!=(const inOrder_iterator& other) const
            {
                return currentNode != other.currentNode;
            }

        };//End class inOrder_iterator
        class postOrder_iterator
        {
        private:

            Node* currentNode;

        public:
            postOrder_iterator(Node* ptr = nullptr): currentNode(ptr){}

            T& operator*() const
            {
                return currentNode->data;
            }

            T* operator->() const
            {
                return &(currentNode->data);
            }


            postOrder_iterator &operator++() {
                if (currentNode == nullptr) {
                    throw std::invalid_argument("Unable to move forward, we have reached the end of the iterator");
                }
                if (currentNode->father == nullptr) {
                    currentNode = nullptr;
                    return *this;
                }
                if (currentNode->father->right == currentNode) { // right child
                    currentNode = currentNode->father;
                    return *this;
                }   // left child
                if (currentNode->father->right != nullptr) {
                    currentNode = currentNode->father->right;
                    while (currentNode->left != nullptr || currentNode->right != nullptr) {
                        if (currentNode->left != nullptr) {
                            currentNode = currentNode->left;
                        } else if (currentNode->right != nullptr) {
                            currentNode = currentNode->right;
                        }
                    }
                    return *this;
                }
                currentNode = currentNode->father;
                return *this;
            }


            postOrder_iterator operator++(int) {
                postOrder_iterator helpIterator = *this;
                if (currentNode == nullptr) {
                    return helpIterator;
                }
                if (currentNode->father == nullptr) {
                    currentNode = nullptr;
                    return helpIterator;
                }
                if (currentNode->father->right == currentNode) { // right child
                    currentNode = currentNode->father;
                    return helpIterator;
                }   // left child
                if (currentNode->father->right != nullptr) {
                    currentNode = currentNode->father->right;
                    while (currentNode->left != nullptr || currentNode->right != nullptr) {
                        if (currentNode->left != nullptr) {
                            currentNode = currentNode->left;
                        } else if (currentNode->right != nullptr) {
                            currentNode = currentNode->right;
                        }
                    }
                    return helpIterator;
                }
                currentNode = currentNode->father;
                return helpIterator;
            }

            bool operator==(const postOrder_iterator& other) const
            {
                return currentNode == other.currentNode;
            }

            bool operator!=(const postOrder_iterator& other) const
            {
                return currentNode != other.currentNode;
            }

        };//End class postOrder_iterator


    private:
        void destroy(Node* node){
            if(node != nullptr){
                destroy(node->right);
                destroy(node->left);
                delete node;
            }
        }

        Node *isInTree(Node *node ,const T& data) {
            if (node != nullptr) {
                if (node->data == data) {
                    return node;
                }
                Node *resultNode = isInTree(node->left,data);
                if (resultNode == nullptr) {
                    resultNode = isInTree(node->right,data);
                }

                return resultNode;

            }
            return nullptr;
        }

        void insertNodes(Node *currentTree, Node *newTree) {
            if (newTree->left != nullptr) {
                add_left(currentTree->data, newTree->left->data);
                insertNodes(currentTree->left, newTree->left);
            }
            if (newTree->right != nullptr) {
                add_right(currentTree->data, newTree->right->data);
                insertNodes(currentTree->right, newTree->right);
            }
        }

        Node *root ;
    public:
        BinaryTree<T>(): root(nullptr){}

        BinaryTree(BinaryTree const &tree) : root(nullptr){
            add_root(tree.root->data);
            insertNodes(this->root, tree.root);
        }
        //move
        BinaryTree(BinaryTree &&other) noexcept {
            this->root = other.root;
            other.root = nullptr;
        }

        ~BinaryTree(){ destroy(this->root);}

        BinaryTree<T> &operator=(const BinaryTree<T> &tree) {

            if (this != &tree) {
                add_root(tree.root->data);
                insertNodes(this->root, tree.root);
                return *this;
            }

            return *this;
        }
        //move
        BinaryTree &operator=(BinaryTree &&treeOther) noexcept {

            this->root = treeOther.root;
            treeOther.root = nullptr;
            return *this;
        }

        BinaryTree& add_root(const T &newRoot){
            if (this->root == nullptr )
            {
                Node *nodeHelp = new Node{newRoot};
                root = nodeHelp;
                return *this;
            }

            root->data = newRoot;
            return *this;
        }

        BinaryTree& add_left(const T& existNode,const T& InsertNode)
        {
            Node *helpNode = isInTree(this->root,existNode);

            if(helpNode == nullptr){throw std::invalid_argument{"The node isn't in the tree"};}

            if(helpNode->left != nullptr)
            {
                helpNode->left->data = InsertNode;
                return *this;
            }

            Node *newNode = new Node{InsertNode};
            newNode->father = helpNode;
            helpNode->left = newNode;
            return *this;

        }

        BinaryTree& add_right(const T& existNode,const T& rightIn)
        {
            Node *helpNode = isInTree(root,existNode);

            if(helpNode == nullptr){throw std::invalid_argument{"The node isn't in the tree"};}

            if(helpNode->right != nullptr)
            {
                helpNode->right->data = rightIn;
                return *this;
            }

            Node *newNode = new Node{rightIn};
            newNode->father = helpNode;
            helpNode->right = newNode;

            return *this;
        }

        preOrder_iterator begin_preorder()
        {
            if (root == nullptr) {
                return preOrder_iterator(nullptr);
            }

            return preOrder_iterator(this->root);
        }

        preOrder_iterator end_preorder(){return preOrder_iterator(nullptr);}

        postOrder_iterator begin_postorder()
        {
            if (root == nullptr)
            {
                return postOrder_iterator(nullptr);
            }

            Node * tmp = root;
            while (tmp->left != nullptr || tmp->right != nullptr)
            {
                if (tmp->left != nullptr) {
                    tmp = tmp->left;
                }

                else if (tmp->right != nullptr )
                {
                    tmp = tmp->right;
                }
            }

            return postOrder_iterator(tmp);
        }

        postOrder_iterator end_postorder()
        {
            return postOrder_iterator(nullptr);
        }

        inOrder_iterator begin_inorder()
        {
            if (root == nullptr)
            {
                return inOrder_iterator(nullptr);
            }

            Node * tmp = root;
            while (tmp->left != nullptr)
            {
                tmp = tmp->left;
            }

            return inOrder_iterator(tmp);
        }

        inOrder_iterator end_inorder()
        {
            return inOrder_iterator(nullptr);
        }

        inOrder_iterator begin() {
            if (root == nullptr) {
                return inOrder_iterator{nullptr};
            }

            Node *tmp = root;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            return inOrder_iterator(tmp);
        }

        inOrder_iterator end() {
            return inOrder_iterator(nullptr);
        }

        friend std::ostream& operator<<(std::ostream& output,const BinaryTree<T> &tree){return output;}

    };
}





#include <fstream> // Add this include directive for ofstream
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
   int key;
   Node* left;
   Node* right;
   int height;
   Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* n) {
   return n ? n->height : 0;
}

int getBalance(Node* n) {
   return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* rightRotate(Node* y) {
   Node* x = y->left;
   Node* T2 = x->right;

   x->right = y;
   y->left = T2;

   y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
   x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

   return x;
}

Node* leftRotate(Node* x) {
   Node* y = x->right;
   Node* T2 = y->left;

   y->left = x;
   x->right = T2;

   x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
   y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

   return y;
}

Node* insert(Node* node, int key) {
   if (!node) return new Node(key);

   if (key < node->key)
       node->left = insert(node->left, key);
   else if (key > node->key) {
       // Please add your code here
       node->right = insert(node->right, key); 
        
	   // end of your code 
   }
   else
       return node; // no duplicates

   // Please add your code here
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
       // node->height =
       // end of your code
   //
   
   int balance = getBalance(node);

   // Balancing
   if (balance > 1 && key < node->left->key)
       return rightRotate(node);
   if (balance < -1 && key > node->right->key)
       // Please add your code here
        return leftRotate(node); 
     
    // end of your code 
   if (balance > 1 && key > node->left->key) {
       node->left = leftRotate(node->left);
       return rightRotate(node);
   }
   if (balance < -1 && key < node->right->key) {
       // Please add your code here
        node->right = rightRotate(node->right);
        return leftRotate(node);
    // 
    // end of your code 
   }

   return node;
}

// Write DOT graph
void exportDOT(Node* root, ofstream& out) {
   if (!root) return;

   if (root->left) {
       out << "    " << root->key << " -> " << root->left->key << ";\n";
       exportDOT(root->left, out);
   }
   else {
       out << "    nullL" << root->key << " [shape=point];\n";
       out << "    " << root->key << " -> nullL" << root->key << ";\n";
   }

   if (root->right) {
       out << "    " << root->key << " -> " << root->right->key << ";\n";
       exportDOT(root->right, out);
   }
   else {
       out << "    nullR" << root->key << " [shape=point];\n";
       out << "    " << root->key << " -> nullR" << root->key << ";\n";
   }
}

void generateDOT(Node* root, const string& filename) {
   ofstream out(filename);
   if (!out) {
       cerr << "Error: Could not open file " << filename << endl;
       return;
   }
   out << "digraph AVLTree {\n";
   out << "    node [fontname=\"Arial\"];\n";

   if (!root)
       out << "\n";
   else
       exportDOT(root, out);

   out << "}\n";
   out.close();
   cout << "DOT file written to " << filename << endl;
}



int main() {
   Node* root = nullptr;
   int values[] = { 3, 2, 1, 4, 5, 6, 7};
   for (int key : values) {
       root = insert(root, key);
   }

   cout << "After insertions, The AVL Tree is saved in the following dot file." << endl;
   generateDOT(root, "avl.dot");
   return 0;
}
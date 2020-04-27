#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 


 

typedef struct TrieNode TrieNode;
struct TrieNode {
    
    char data; //the letter stored
    TrieNode* children[26];//array of 26 letters
    int leaf;//flag-counter used to check end of word
};

TrieNode* make_trienode(char data) {
    // Allocating dynaminc memory for the array using calloc
    TrieNode* node = (TrieNode*) calloc (1, sizeof(TrieNode));
    for (int i=0; i<26; i++)
        node->children[i] = NULL;
    node->leaf = 0;
    node->data = data;
    return node;
}
 
void free_trie(TrieNode* node) {
    // this is supposed to be done to free the memory taken up by the node
    for(int i=0; i<26; i++) {
        if (node->children[i] != NULL) {
            free_trie(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}
 
TrieNode* insert_trie(TrieNode* root, char word[20]) {
    //function for adding word to trie(lowercase)
    TrieNode* temp = root;
 
    for (int i=0; word[i] != '\0'; i++) {
        
    int idx = (int) word[i] - 'a';
        if (temp->children[idx] == NULL) {
          //if empty make
            temp->children[idx] = make_trienode(word[i]);
        }
        else { }
        temp = temp->children[idx];
    }
    
    temp->leaf = 1;//this is flag
    return root;
}
 
int search_trie(TrieNode* root, char* word)
{
    // Searches for word in the Trie tree
    TrieNode* temp = root;
 
    for(int i=0; word[i]!='\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->leaf == 1)
        return 1;
    return 0;
}
 

 
void print_search(TrieNode* root, char word[20]) {
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}
 
int main() {
   
    TrieNode* root = make_trienode('\0');//end of line
    int n; char w[20];
    printf("How many words?");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter word you want to insert: ");
        scanf("%s",w);
        root=insert_trie(root,w);
    }
  
    char s[20];
    printf("Enter word to search: ");
    scanf("%s",s);
    print_search(root, s);
    free_trie(root);
    return 0;
}
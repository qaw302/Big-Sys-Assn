// Hash Linked List

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SIZE = 10;
struct bucket* hashTable = NULL;
// typedef char* Key;


typedef struct Node{
    int key;
    int value;
    struct Node *next;    
}Node;

typedef struct bucket{
    Node* head; //젤 처음 노드 가리킴
    int count; //노드 몇개가 있는지.
}bucket;


//hash함수
int hashFunction(int key){
    return key/SIZE;
}

//노드 생성 함수
Node* createNode(int key, int value){

    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));

    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    
    return newNode;
}

//노드 삽입
void insert_node(int key, int value){

    int hashIndex = hashFunction(key);

    Node *newNode = createNode(key, value);


    if(hashTable[hashIndex].count == 0){    // 인덱스에 노드가 없는 경우
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count = 1;
    }
    else{   //인덱스에 노드가 있는 경우
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

//노드 제거
void remove_node(int key){
    int hashIndex = hashFunction(key);

    Node* cur;
    Node* trace;

    cur = hashTable[hashIndex].head;

    if(cur == NULL){
        printf("존재하지 않는 key 입니다.\n");
        return;
    }
    
    while(cur != NULL){
        if(cur->key == key){
            if(cur == hashTable[hashIndex].head){
                hashTable[hashIndex].head = cur->next;
            }
            else{
                trace->next = cur->next;
            }
            hashTable[hashIndex].count--;
            free(cur);
            return;
        }
        trace = cur;
        cur = cur->next;
    }

    printf("key가 존재하지 않습니다.\n");
    return;

}

//노드 검색
void search_node(int key){
    int hashIndex = hashFunction(key);

    Node* cur;

    cur = hashTable[hashIndex].head;

    if(cur == NULL){
        printf("존재하지 않는 key 입니다.\n");
        return;
    }
    
    while(cur != NULL){
        if(cur->key == key){
            printf("key = %d, value = %d\n", cur->key, cur->value);
            return;
        }
        cur = cur->next;
    }

    printf("key가 존재하지 않습니다.\n");
    return;
}


void view_table(){
    Node* scan;
    int i = 0;
    for(i=0; i<SIZE; i++){
        scan = hashTable[i].head;
        printf("bucket[%d] : ", i);
    
        while(scan != NULL){
            printf("(key: %d, value: %d)->",scan->key,scan->value);
            scan = scan->next;
        }

        printf("\n");
    }
    printf("=")*30;
    return;
}


int main()
{
    hashTable = (bucket*)malloc(SIZE*sizeof(bucket));

    int key;
    int value;
    int num;


    while(1){
        printf("=====================================");
        printf("\n");
        printf("1.추가 2.삭제 3.검색 4.테이블 0.종료\n : ");
        scanf("%d", &num);

        if(num == 1){
            printf("key: ");
            scanf("%d", &key);
            printf("value: ");
            scanf("%d", &value);

            insert_node(key, value);

            continue;
        }
        else if(num == 2){
            printf("key: ");
            scanf("%d", &key);

            remove_node(key);

            continue;
        }
        else if(num == 3){
            printf("key: ");
            scanf("%d", &key);

            search_node(key);

            continue;
        }
        else if(num == 4){
            view_table();

            continue;
        }
        else{
            printf("종료\n");

            break;
        }
    }

    return 0;
}
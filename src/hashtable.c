#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket entry struct.
  // 3. Append to the linked list or create it if it does not yet exist.
  //char* str = (char*)key;
  //printf("inside insert, key: %s\n", str);
  unsigned int bucket_location = (*table->hashFunction)(key) % table->size;
  //printf("bucket location : %d\n", bucket_location);
  HashBucketEntry* pointer = NULL;
  if (!table->buckets[bucket_location]) {
    //printf("inside if \n");
    table->buckets[bucket_location] = malloc(sizeof(HashBucketEntry));
    pointer = table->buckets[bucket_location];
  } else {
    //printf("inside else\n");
    pointer = table->buckets[bucket_location];
    while (pointer->next != NULL) {
      pointer = pointer->next;
    }
    pointer->next = malloc(sizeof(HashBucketEntry));
    pointer = pointer->next; 
  }
  //printf("reached here in insetion\n");  
  pointer->key = key;
  pointer->data = data;
  pointer->next = NULL;
  //printf("finished insertion\n"); 
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  //char* str = (char*)key;
  //printf("inside find key: %s\n", str);
  unsigned int bucket_location = (*table->hashFunction)(key) % table->size;
  HashBucketEntry* pointer = table->buckets[bucket_location];
  while (pointer) {
    if ((*table->equalFunction)(pointer->key, key)) {
      //printf("found key\n");
      return pointer->data; 
    }
    pointer = pointer->next;
  }
  //printf("didn't found key\n");
  return NULL;
} 

/* Task 2.1 */
unsigned int stringHash(void *s) {
  // -- TODO --
  unsigned int hash_value = 0;
  unsigned int prime_base = 31;
  unsigned int mod = 1000000007;
  char* str = (char*) s;
  while (*str != '\0') {
    hash_value = (hash_value * prime_base + *str) % mod; 
    ++str; 
 }
  return hash_value;
  //fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  // return 0;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  char* str1 = s1;
  char* str2 = s2;
  while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
    ++str1;
    ++str2;
  }
  if (*str1 == '\0' && *str2 == '\0') {
    return 1;
  } 
  return 0;
  //fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */
  //return 0;
}

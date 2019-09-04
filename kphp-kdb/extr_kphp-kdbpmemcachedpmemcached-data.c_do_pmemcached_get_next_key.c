#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct index_entry {int data_len; char* data; int key_len; } ;
struct hash_entry {int key_len; char* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_load_local (char*,int,struct hash_entry*,struct index_entry*) ; 
 struct hash_entry* get_next_entry (char const*,int) ; 
 struct index_entry* index_get_next (char const*,int) ; 
 int mystrcmp (char*,int,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int) ; 

int do_pmemcached_get_next_key (const char *key, int key_len, char **result_key, int *result_key_len) {
  char *cur_key = 0;
  int cur_key_len = 0;
  struct hash_entry *hash_entry = get_next_entry (key, key_len);
  int r = -1;
  if (hash_entry) {
    cur_key_len = hash_entry->key_len;
    cur_key = hash_entry->key;
    r = 0;
  }
  struct index_entry *index_entry = index_get_next (key, key_len);
  if (!index_entry) {    
    return -2;
  }
  vkprintf (4, "next in index: %d, next in memory: %d\n", index_entry->data_len != -1, r != -1);
  if (index_entry->data_len == -1 && r == -1) {
    return -1;
  }
  int c;
  if (index_entry->data_len == -1) {
    c = -1;
  } else if (!cur_key) {
    c = 1;
  } else {
    c = mystrcmp (cur_key, cur_key_len, index_entry->data, index_entry->key_len);
  }
  if (c <= 0) {
    *result_key = cur_key;
    *result_key_len = cur_key_len;
  } else {
    *result_key = index_entry->data;
    *result_key_len = index_entry->key_len;
  }
  cache_load_local (*result_key, *result_key_len, (c <= 0) ? hash_entry : 0, (c >= 0) ? index_entry : 0);
  return 0;
}
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_load_local (char*,int,struct hash_entry*,struct index_entry*) ; 
 struct index_entry* index_entry_next (struct index_entry*) ; 
 struct index_entry* iterator_index_entry ; 
 int /*<<< orphan*/  iterator_key ; 
 int iterator_prefix_len ; 
 int mystrcmp (char*,int,char*,int) ; 
 int mystrcmp2 (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct index_entry*,struct hash_entry*) ; 
 scalar_t__ wildcard_report () ; 

int iterator_report (struct hash_entry *hash_entry) {
  vkprintf (3, "iterator_report: index_entry %p, hash_entry %p\n", iterator_index_entry, hash_entry);
  struct index_entry *index_entry = iterator_index_entry;
  char *cur_key = 0;
  int cur_key_len = 0;
  int r = -1;
  if (hash_entry) {
    cur_key_len = hash_entry->key_len;
    cur_key = hash_entry->key;
    r = 0;
  }
  int c;
  while (1) {
    if (index_entry->data_len == -1) {
      c = -1;
    } else if (!cur_key) {
      c = 1;
    } else {
      c = mystrcmp (cur_key, cur_key_len, index_entry->data, index_entry->key_len);
    }
    if (c <= 0) {
      break;
    }
    if (!hash_entry) {
      int x = mystrcmp2 (iterator_key, iterator_prefix_len, index_entry->data, index_entry->key_len, 0);
      assert (x <= 0);
      if (x && x >= -iterator_prefix_len) {
        return 0;
      }
    }
    //fprintf (stderr, ".");
    cache_load_local (index_entry->data, index_entry->key_len, (c <= 0) ? hash_entry : 0, (c >= 0) ? index_entry : 0);
    if (wildcard_report () < 0) {
      return -1;
    }

    index_entry = index_entry_next (index_entry);
    if (!index_entry) {
      return -2;
    }
  }
  if (!hash_entry) {
    return 0;
  }
  cache_load_local (hash_entry->key, hash_entry->key_len, (c <= 0) ? hash_entry : 0, (c >= 0) ? index_entry : 0);
  //fprintf (stderr, "-");
  if (wildcard_report () < 0) { return -1;};
  if (c == 0) {
    index_entry = index_entry_next (index_entry);
    if (!index_entry) {
      return -2;
    }
  }
  iterator_index_entry = index_entry;
  return 0;
}
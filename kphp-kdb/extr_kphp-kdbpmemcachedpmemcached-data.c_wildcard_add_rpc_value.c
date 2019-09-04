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
struct wildcard_entry {int key_len; int data_len; scalar_t__ flags; void* data; void* key; } ;
struct data {int data_len; } ;
typedef  int /*<<< orphan*/  hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 scalar_t__ memory_for_wildcard_cache ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wildcard_add_use (struct wildcard_entry*) ; 
 int /*<<< orphan*/  wildcard_cache_entries ; 
 scalar_t__ wildcard_cache_memory ; 
 int /*<<< orphan*/  wildcard_free_lru () ; 
 struct data wildcard_get_value (char const*,int) ; 
 int /*<<< orphan*/  wildcard_rpc_cache_tree ; 
 void* zzmalloc (int) ; 

void wildcard_add_rpc_value (const char *key, int key_len, const char *data, int data_len) {
  while (wildcard_cache_memory + data_len + key_len + sizeof (struct wildcard_entry) > memory_for_wildcard_cache) {
    wildcard_free_lru ();
  }
  struct data x = wildcard_get_value (key, key_len);
  if (x.data_len != -1) {
    return;
  }
  struct wildcard_entry *entry = zzmalloc (sizeof (struct wildcard_entry));
  wildcard_add_use (entry);
  entry->key_len = key_len;
  entry->key = zzmalloc (key_len);
  memcpy (entry->key, key, key_len);
  entry->data_len = data_len;
  entry->data = zzmalloc (data_len);
  memcpy (entry->data, data, data_len);
  entry->flags = 0;
  wildcard_rpc_cache_tree = tree_insert (wildcard_rpc_cache_tree, (hash_entry_t *)entry, lrand48 ());
  wildcard_cache_memory += data_len + key_len + sizeof (struct wildcard_entry);
  wildcard_cache_entries ++;
}
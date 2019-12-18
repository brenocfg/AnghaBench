#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int data_len; } ;
struct entry {int key_len; TYPE_1__ data; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 long long HASH_TABLE_MASK ; 
 int HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  add_cache_use (int) ; 
 int /*<<< orphan*/  assert (size_t) ; 
 struct entry* cache ; 
 size_t cache_free ; 
 int* cache_next ; 
 int* cache_prev ; 
 int* cache_stack ; 
 int /*<<< orphan*/  create_new_cache_item (struct entry*,char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_cache () ; 
 long long get_hash (char const*,int) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_cache_use (int) ; 
 int verbosity ; 

struct entry *get_cache_item (const char *key, int key_len) {
  if (verbosity >= 4) { fprintf (stderr, "get_cache_item\n"); }
  long long key_hash = get_hash (key, key_len);
  int h = key_hash & HASH_TABLE_MASK;
  int n = h + HASH_TABLE_SIZE;
  while (cache_next[n] < HASH_TABLE_SIZE) {
    struct entry *e = cache + cache_next[n];
    if (key_len == e->key_len && key_len >= 0 && !memcmp (key, e->key, key_len)) {
      update_cache_use (cache_next[n]);
      if (verbosity >= 4) {
        fprintf (stderr, "cache found data_len=%d (key_len = %d key = %s)\n", e->data.data_len, key_len, key);
      }
      return e;
    }
    n = cache_next[n];
  }
  if (verbosity >= 4) {
    fprintf (stderr, "cache not found (key_len = %d key = %s)...\n", key_len, key);
  }
  assert (cache_free);
  int e = cache_stack [--cache_free];
  cache_next[e] = cache_next[n];
  cache_prev[cache_next[e]] = e;
  cache_prev[e] = n;
  cache_next[n] = e;
  create_new_cache_item (cache + e, key, key_len);
  free_cache ();
  add_cache_use (e);
  return cache + e;
}
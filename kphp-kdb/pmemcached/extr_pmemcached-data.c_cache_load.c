#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {long long accum_value; int data_len; } ;
struct TYPE_8__ {int data_len; } ;
struct TYPE_9__ {char const* key; int key_len; TYPE_1__ data; scalar_t__ index_entry; TYPE_4__* hash_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int cache_assign_index_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  cache_miss ; 
 int /*<<< orphan*/  cache_ok ; 
 int /*<<< orphan*/  cache_reload (TYPE_2__*) ; 
 TYPE_2__* current_cache ; 
 int /*<<< orphan*/  debug_dump_key (char const*,int) ; 
 int /*<<< orphan*/  del_entry (TYPE_4__*) ; 
 scalar_t__ disable_cache ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* get_cache_item (char const*,int) ; 
 TYPE_2__* get_cache_item_simple (char const*,int) ; 
 int /*<<< orphan*/  pmemcached_incr_current (long long) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int cache_load (const char *key, int key_len, int forceload) {
  if (verbosity >= 4) {
    fprintf (stderr, "loading cache item... ");
  }
  //current_cache = get_cache_item (key, key_len);
  current_cache = disable_cache ? get_cache_item_simple (key, key_len) : get_cache_item (key, key_len);
  if (verbosity >= 4) {
    fprintf (stderr, "current_cache->data.data_len = %d\n", current_cache->data.data_len);
    fprintf (stderr, "forceload = %d\n", forceload);
    fprintf (stderr, "current_cache->key = "); debug_dump_key (current_cache->key, current_cache->key_len);
    fprintf (stderr, "key = "); debug_dump_key (key, key_len);
    fprintf (stderr, "key_len = %d, current_cache->key_len = %d\n", key_len, current_cache->key_len);
  }
  assert (key_len >= 0);
  if (!forceload || current_cache->data.data_len != -2) {
    cache_ok++;
    if (verbosity >= 4) {
      fprintf (stderr, "already in cache\n");
    }
    cache_reload (current_cache);  
    return current_cache->data.data_len == -1 ? 0 : 1;
  } else { 
    cache_miss++;
    if (verbosity >= 4) {
      fprintf (stderr, "not in cache. Adding...");
    }

    cache_reload (current_cache);

    if (!current_cache->hash_entry || current_cache->data.data_len == -2) {
      if (forceload) {
        if (verbosity >= 4) {
          fprintf (stderr, "Copying data from index...");
        }
        if (cache_assign_index_entry (current_cache) == -2) {
          if (verbosity >= 4) {
            fprintf (stderr, "Data is not loaded. Using aio.\n");
          }
          return -2;
        }
        if (current_cache->hash_entry && current_cache->hash_entry->accum_value) {
          assert (current_cache->hash_entry->data_len == -2);
          if (verbosity >= 4) {
            fprintf (stderr, "Adding accumulated data...");
          }
          long long arg = current_cache->hash_entry->accum_value;
          del_entry (current_cache->hash_entry);
          current_cache->hash_entry = 0;
          if (current_cache->index_entry) {
            pmemcached_incr_current (arg);
          }
        }
      } else {
        if (verbosity >= 4) {
          fprintf (stderr, "Skipping loading data from index, because forceload set to 0...");
        }
      }
      if (verbosity >= 4) {
        fprintf (stderr, "Added successfully.\n");
      }
    }                                                                               
    return current_cache->data.data_len == -1 ? 0 : 1;
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int key_len; scalar_t__ key; } ;
struct TYPE_5__ {struct TYPE_5__* prev_time; struct TYPE_5__* next_time; } ;
struct TYPE_4__ {struct TYPE_4__* prev_use; struct TYPE_4__* next_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_TIME_ID (int /*<<< orphan*/ ) ; 
 int HASH_TABLE_SIZE ; 
 int TIME_TABLE_SIZE ; 
 TYPE_3__* cache ; 
 int cache_free ; 
 int* cache_next ; 
 int* cache_next_use ; 
 int* cache_prev ; 
 int* cache_prev_use ; 
 int* cache_stack ; 
 scalar_t__ del_by_LRU ; 
 int /*<<< orphan*/  disable_cache ; 
 TYPE_2__* entry_buffer ; 
 int /*<<< orphan*/  get_double_time_since_epoch () ; 
 int /*<<< orphan*/  init_memory_bounds () ; 
 int /*<<< orphan*/  last_del_time ; 
 scalar_t__ malloc_mem ; 
 size_t* time_st ; 
 scalar_t__ tree ; 
 scalar_t__ wildcard_cache_tree ; 
 TYPE_1__ wildcard_use ; 

void init_hash_table (void) {
  int i;

  tree = 0;
  wildcard_cache_tree = 0;
  wildcard_use.next_use = &wildcard_use;
  wildcard_use.prev_use = &wildcard_use;

  for (i = 0; i < TIME_TABLE_SIZE; i++) {
    time_st[i] = i;

    entry_buffer[time_st[i]].next_time = &entry_buffer[time_st[i]];
    entry_buffer[time_st[i]].prev_time = &entry_buffer[time_st[i]];
  }


  last_del_time = GET_TIME_ID (get_double_time_since_epoch());
  malloc_mem = 0;
  del_by_LRU = 0;

  if (!disable_cache) {
    for (i=0; i < HASH_TABLE_SIZE; i++) {
      cache[i].key_len = -1;
      cache[i].key = 0;
      cache_next [HASH_TABLE_SIZE + i] = HASH_TABLE_SIZE + i;
      cache_prev [HASH_TABLE_SIZE + i] = HASH_TABLE_SIZE + i;
      cache_stack[i] = i;
    }

    cache_prev_use [HASH_TABLE_SIZE] = HASH_TABLE_SIZE;
    cache_next_use [HASH_TABLE_SIZE] = HASH_TABLE_SIZE;
    cache_free = HASH_TABLE_SIZE;
  }
  init_memory_bounds ();
}
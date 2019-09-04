#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data_len; int delay; } ;
struct TYPE_5__ {scalar_t__ index_entry; int /*<<< orphan*/  hash_entry; TYPE_1__ data; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int DELAY_INFINITY ; 
 int /*<<< orphan*/  cache_reload (TYPE_2__*) ; 
 TYPE_2__* current_cache ; 
 int /*<<< orphan*/  del_entry (int /*<<< orphan*/ ) ; 
 int get_double_time_since_epoch () ; 
 int /*<<< orphan*/  on_value_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmct_set ; 
 int /*<<< orphan*/  pmemcached_store_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int pmemcached_delete_current (void) {
  if (current_cache->data.data_len == -1) {
    return -1;
  }
  on_value_change (current_cache->key, current_cache->key_len);
  int delay = current_cache->data.delay;
  if (current_cache->index_entry != 0) {
    pmemcached_store_current (pmct_set, 0, -1, 0, -1);
  } else {
    del_entry (current_cache->hash_entry);
  }
  cache_reload (current_cache);
  if (delay < get_double_time_since_epoch() && delay != DELAY_INFINITY) {
    return -1;
  }
  return 1;
}
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
struct lev_delete_counter64 {long long cnt_id; } ;
struct lev_delete_counter {long long cnt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_STATS_DELETE_COUNTER ; 
 int /*<<< orphan*/  LEV_STATS_DELETE_COUNTER_64 ; 
 void* alloc_log_event (int /*<<< orphan*/ ,int,long long) ; 
 int /*<<< orphan*/  get_counter_f (long long,int) ; 
 int* index_deleted ; 
 int index_get_idx (long long) ; 
 int index_size ; 

int delete_counter (long long counter_id, int replay) {
  if (!replay) {
    if (counter_id == (int)counter_id) {
      struct lev_delete_counter *LV = alloc_log_event (LEV_STATS_DELETE_COUNTER, sizeof (struct lev_delete_counter), counter_id);
      LV->cnt_id = counter_id;
    } else {
      struct lev_delete_counter64 *LV = alloc_log_event (LEV_STATS_DELETE_COUNTER_64, sizeof (struct lev_delete_counter64), counter_id);
      LV->cnt_id = counter_id;
    }
  }
  get_counter_f (counter_id, -1);
  int l = index_get_idx (counter_id);
  if (l < index_size) {
    index_deleted[l] = 1;
  }
  return 1;
}
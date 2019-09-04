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
struct lev_search_set_hash {long long obj_id; long long hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_SEARCH_SET_HASH ; 
 struct lev_search_set_hash* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fits (long long) ; 
 int set_hash (long long,long long) ; 

int do_set_hash (long long item_id, long long hash) {
  if (!fits (item_id)) { return 0; }
  struct lev_search_set_hash *LR = alloc_log_event (LEV_SEARCH_SET_HASH, 20, 0);
  LR->obj_id = item_id;
  LR->hash = hash;
  return set_hash (item_id, hash);
}
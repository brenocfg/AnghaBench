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
struct lev_search_set_rates {long long obj_id; int rate2; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_SEARCH_SET_RATES ; 
 struct lev_search_set_rates* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fits (long long) ; 
 int set_rates (long long,int,int) ; 

int do_set_rates (long long item_id, int rate, int rate2) {
  if (!fits (item_id)) { return 0; }
  struct lev_search_set_rates *LR = alloc_log_event (LEV_SEARCH_SET_RATES, 20, rate);
  LR->obj_id = item_id;
  LR->rate2 = rate2;
  return set_rates (item_id, rate, rate2);
}
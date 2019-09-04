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
struct lev_search_incr_rate_short {long long obj_id; } ;
struct lev_search_incr_rate {long long obj_id; } ;

/* Variables and functions */
 scalar_t__ LEV_SEARCH_INCR_RATE2 ; 
 scalar_t__ LEV_SEARCH_INCR_RATE2_SHORT ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  fits (long long) ; 
 int incr_rate2 (long long,int) ; 

int do_incr_rate2 (long long item_id, int rate2_incr) {
  if (!fits (item_id)) { return 0; }
  if (rate2_incr == (signed char) rate2_incr) {
    struct lev_search_incr_rate_short *IS = alloc_log_event (LEV_SEARCH_INCR_RATE2_SHORT + (rate2_incr & 0xff), 12, 0);
    IS->obj_id = item_id;
  } else {
    struct lev_search_incr_rate *IL = alloc_log_event (LEV_SEARCH_INCR_RATE2, 16, rate2_incr);
    IL->obj_id = item_id;
  }
  return incr_rate2 (item_id, rate2_incr);
}
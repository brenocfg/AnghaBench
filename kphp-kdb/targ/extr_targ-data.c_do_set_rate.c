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
struct lev_rate {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_RATE ; 
 struct lev_rate* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_user (int) ; 
 int /*<<< orphan*/  set_rate (struct lev_rate*) ; 

int do_set_rate (int user_id, int rate) {
  if (!get_user (user_id)) { return 0; }
  struct lev_rate *E = alloc_log_event (LEV_TARG_RATE, 12, user_id);
  E->rate = rate;
  set_rate (E);
  return 1;
}
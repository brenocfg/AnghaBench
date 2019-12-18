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
typedef  int /*<<< orphan*/  user_t ;
struct lev_military {int unit_id; int start; int finish; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_MIL_ADD ; 
 struct lev_military* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * get_user (int) ; 
 int /*<<< orphan*/  store_military (int /*<<< orphan*/ *,struct lev_military*) ; 

int do_set_military (int user_id, int unit_id, int start, int finish) {
  user_t *U = get_user (user_id);
  if (!U) {
    return 0;
  }

  struct lev_military *E = alloc_log_event (LEV_TARG_MIL_ADD, sizeof (struct lev_military), user_id);

  E->unit_id = unit_id;
  E->start = start;
  E->finish = finish;

  store_military (U, E);
  return 1;
}
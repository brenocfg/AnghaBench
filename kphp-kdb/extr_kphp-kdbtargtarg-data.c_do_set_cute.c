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
struct lev_cute {int cute; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_CUTE ; 
 struct lev_cute* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_user (int) ; 
 int /*<<< orphan*/  set_cute (struct lev_cute*) ; 

int do_set_cute (int user_id, int cute) {
  if (!get_user (user_id)) { return 0; }
  struct lev_cute *E = alloc_log_event (LEV_TARG_CUTE, 12, user_id);
  E->cute = cute;
  set_cute (E);
  return 1;
}
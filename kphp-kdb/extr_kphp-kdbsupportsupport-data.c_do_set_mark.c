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
struct lev_support_set_mark {int mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_SUPPORT_SET_MARK ; 
 struct lev_support_set_mark* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int set_mark (struct lev_support_set_mark*) ; 

int do_set_mark (int user_id, int mark) {
  struct lev_support_set_mark *E =
    alloc_log_event (LEV_SUPPORT_SET_MARK, sizeof (struct lev_support_set_mark), user_id);

  E->mark = mark;

  return set_mark (E);
}
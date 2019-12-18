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
struct lev_support_delete_answer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_SUPPORT_DELETE_ANSWER ; 
 struct lev_support_delete_answer* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int delete_answer (struct lev_support_delete_answer*) ; 

int do_delete_answer (int user_id) {
  struct lev_support_delete_answer *E =
    alloc_log_event (LEV_SUPPORT_DELETE_ANSWER, sizeof (struct lev_support_delete_answer), user_id);

  return delete_answer (E);
}
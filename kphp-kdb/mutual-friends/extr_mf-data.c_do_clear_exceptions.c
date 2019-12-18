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
struct lev_mf_clear_exceptions {int user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_MF_CLEAR_EXCEPTIONS ; 
 struct lev_mf_clear_exceptions* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int clear_exceptions (struct lev_mf_clear_exceptions*) ; 

int do_clear_exceptions (int uid) {
  struct lev_mf_clear_exceptions *E =
    alloc_log_event (LEV_MF_CLEAR_EXCEPTIONS, sizeof (struct lev_mf_clear_exceptions), 0);

  E->user_id = uid;

  return clear_exceptions (E);
}
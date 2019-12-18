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

/* Variables and functions */
 int /*<<< orphan*/  TD_SIGNO_MASK ; 
 int /*<<< orphan*/  TD_THR_ANY_STATE ; 
 int /*<<< orphan*/  TD_THR_ANY_USER_FLAGS ; 
 int /*<<< orphan*/  TD_THR_LOWEST_PRIORITY ; 
 int /*<<< orphan*/  info_cb ; 
 int /*<<< orphan*/  main_ta ; 
 int /*<<< orphan*/  p_td_ta_thr_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
info_solthreads (char *args, int from_tty)
{
  p_td_ta_thr_iter (main_ta, info_cb, args,
		    TD_THR_ANY_STATE, TD_THR_LOWEST_PRIORITY,
		    TD_SIGNO_MASK, TD_THR_ANY_USER_FLAGS);
}
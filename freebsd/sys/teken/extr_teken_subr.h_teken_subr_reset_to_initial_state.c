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
typedef  int /*<<< orphan*/  teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TP_SHOWCURSOR ; 
 int /*<<< orphan*/  teken_funcs_cursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_funcs_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  teken_subr_do_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_subr_erase_display (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
teken_subr_reset_to_initial_state(teken_t *t)
{

	teken_subr_do_reset(t);
	teken_subr_erase_display(t, 2);
	teken_funcs_param(t, TP_SHOWCURSOR, 1);
	teken_funcs_cursor(t);
}
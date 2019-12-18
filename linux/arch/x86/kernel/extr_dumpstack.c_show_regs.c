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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEFAULT ; 
 int /*<<< orphan*/  SHOW_REGS_ALL ; 
 int /*<<< orphan*/  SHOW_REGS_USER ; 
 int /*<<< orphan*/  __show_regs (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  show_regs_print_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_trace_log_lvl (int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void show_regs(struct pt_regs *regs)
{
	show_regs_print_info(KERN_DEFAULT);

	__show_regs(regs, user_mode(regs) ? SHOW_REGS_USER : SHOW_REGS_ALL);

	/*
	 * When in-kernel, we also print out the stack at the time of the fault..
	 */
	if (!user_mode(regs))
		show_trace_log_lvl(current, regs, NULL, KERN_DEFAULT);
}
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
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  die (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_user_fault (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void default_trap_handler(struct pt_regs *regs)
{
	if (user_mode(regs)) {
		report_user_fault(regs, SIGSEGV, 0);
		do_exit(SIGSEGV);
	} else
		die(regs, "Unknown program exception");
}
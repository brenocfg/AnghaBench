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
 int TRAP (struct pt_regs*) ; 
 scalar_t__ __die (char const*,struct pt_regs*,long) ; 
 scalar_t__ debugger (struct pt_regs*) ; 
 unsigned long oops_begin (struct pt_regs*) ; 
 int /*<<< orphan*/  oops_end (unsigned long,struct pt_regs*,long) ; 

void die(const char *str, struct pt_regs *regs, long err)
{
	unsigned long flags;

	/*
	 * system_reset_excption handles debugger, crash dump, panic, for 0x100
	 */
	if (TRAP(regs) != 0x100) {
		if (debugger(regs))
			return;
	}

	flags = oops_begin(regs);
	if (__die(str, regs, err))
		err = 0;
	oops_end(flags, regs, err);
}
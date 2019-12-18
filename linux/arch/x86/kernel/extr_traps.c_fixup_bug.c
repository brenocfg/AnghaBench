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
struct pt_regs {int /*<<< orphan*/  ip; } ;

/* Variables and functions */
#define  BUG_TRAP_TYPE_BUG 130 
#define  BUG_TRAP_TYPE_NONE 129 
#define  BUG_TRAP_TYPE_WARN 128 
 int /*<<< orphan*/  LEN_UD2 ; 
 int X86_TRAP_UD ; 
 int report_bug (int /*<<< orphan*/ ,struct pt_regs*) ; 

int fixup_bug(struct pt_regs *regs, int trapnr)
{
	if (trapnr != X86_TRAP_UD)
		return 0;

	switch (report_bug(regs->ip, regs)) {
	case BUG_TRAP_TYPE_NONE:
	case BUG_TRAP_TYPE_BUG:
		break;

	case BUG_TRAP_TYPE_WARN:
		regs->ip += LEN_UD2;
		return 1;
	}

	return 0;
}
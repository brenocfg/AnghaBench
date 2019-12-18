#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned int pc; unsigned long sp; int tsr; } ;
struct TYPE_3__ {unsigned long usp; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 

void start_thread(struct pt_regs *regs, unsigned int pc, unsigned long usp)
{
	/*
	 * The binfmt loader will setup a "full" stack, but the C6X
	 * operates an "empty" stack. So we adjust the usp so that
	 * argc doesn't get destroyed if an interrupt is taken before
	 * it is read from the stack.
	 *
	 * NB: Library startup code needs to match this.
	 */
	usp -= 8;

	regs->pc  = pc;
	regs->sp  = usp;
	regs->tsr |= 0x40; /* set user mode */
	current->thread.usp = usp;
}
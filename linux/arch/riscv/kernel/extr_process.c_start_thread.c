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
struct pt_regs {unsigned long sepc; unsigned long sp; int /*<<< orphan*/  sstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_FS_INITIAL ; 
 int /*<<< orphan*/  SR_SPIE ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fstate_restore (int /*<<< orphan*/ ,struct pt_regs*) ; 
 scalar_t__ has_fpu ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

void start_thread(struct pt_regs *regs, unsigned long pc,
	unsigned long sp)
{
	regs->sstatus = SR_SPIE;
	if (has_fpu) {
		regs->sstatus |= SR_FS_INITIAL;
		/*
		 * Restore the initial value to the FP register
		 * before starting the user program.
		 */
		fstate_restore(current, regs);
	}
	regs->sepc = pc;
	regs->sp = sp;
	set_fs(USER_DS);
}
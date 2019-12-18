#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/  pc; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  __die_if_kernel (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

void
do_illegal_instruction(struct pt_regs *regs)
{
	__die_if_kernel("Illegal instruction in kernel", regs, SIGKILL);

	/* If in user mode, send SIGILL signal to current process. */

	pr_info_ratelimited("Illegal Instruction in '%s' (pid = %d, pc = %#010lx)\n",
			    current->comm, task_pid_nr(current), regs->pc);
	force_sig(SIGILL);
}
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
struct pt_regs {unsigned long r1; unsigned long r20; unsigned long r19; int pt_mode; int msr; unsigned long r15; int /*<<< orphan*/  r10; int /*<<< orphan*/  r21; } ;
struct thread_info {struct pt_regs cpu_context; } ;
struct task_struct {int flags; } ;
struct cpu_context {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int MSR_EE ; 
 int MSR_EIP ; 
 int MSR_IE ; 
 int MSR_UMS ; 
 int MSR_VM ; 
 int MSR_VMS ; 
 int PF_KTHREAD ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  local_save_flags (int) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 scalar_t__ ret_from_kernel_thread ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long arg, struct task_struct *p)
{
	struct pt_regs *childregs = task_pt_regs(p);
	struct thread_info *ti = task_thread_info(p);

	if (unlikely(p->flags & PF_KTHREAD)) {
		/* if we're creating a new kernel thread then just zeroing all
		 * the registers. That's OK for a brand new thread.*/
		memset(childregs, 0, sizeof(struct pt_regs));
		memset(&ti->cpu_context, 0, sizeof(struct cpu_context));
		ti->cpu_context.r1  = (unsigned long)childregs;
		ti->cpu_context.r20 = (unsigned long)usp; /* fn */
		ti->cpu_context.r19 = (unsigned long)arg;
		childregs->pt_mode = 1;
		local_save_flags(childregs->msr);
#ifdef CONFIG_MMU
		ti->cpu_context.msr = childregs->msr & ~MSR_IE;
#endif
		ti->cpu_context.r15 = (unsigned long)ret_from_kernel_thread - 8;
		return 0;
	}
	*childregs = *current_pt_regs();
	if (usp)
		childregs->r1 = usp;

	memset(&ti->cpu_context, 0, sizeof(struct cpu_context));
	ti->cpu_context.r1 = (unsigned long)childregs;
#ifndef CONFIG_MMU
	ti->cpu_context.msr = (unsigned long)childregs->msr;
#else
	childregs->msr |= MSR_UMS;

	/* we should consider the fact that childregs is a copy of the parent
	 * regs which were saved immediately after entering the kernel state
	 * before enabling VM. This MSR will be restored in switch_to and
	 * RETURN() and we want to have the right machine state there
	 * specifically this state must have INTs disabled before and enabled
	 * after performing rtbd
	 * compose the right MSR for RETURN(). It will work for switch_to also
	 * excepting for VM and UMS
	 * don't touch UMS , CARRY and cache bits
	 * right now MSR is a copy of parent one */
	childregs->msr &= ~MSR_EIP;
	childregs->msr |= MSR_IE;
	childregs->msr &= ~MSR_VM;
	childregs->msr |= MSR_VMS;
	childregs->msr |= MSR_EE; /* exceptions will be enabled*/

	ti->cpu_context.msr = (childregs->msr|MSR_VM);
	ti->cpu_context.msr &= ~MSR_UMS; /* switch_to to kernel mode */
	ti->cpu_context.msr &= ~MSR_IE;
#endif
	ti->cpu_context.r15 = (unsigned long)ret_from_fork - 8;

	/*
	 *  r21 is the thread reg, r10 is 6th arg to clone
	 *  which contains TLS area
	 */
	if (clone_flags & CLONE_SETTLS)
		childregs->r21 = childregs->r10;

	return 0;
}
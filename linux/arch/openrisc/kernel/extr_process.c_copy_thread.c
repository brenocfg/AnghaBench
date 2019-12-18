#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int flags; } ;
struct pt_regs {unsigned long* gpr; unsigned long sp; } ;
struct TYPE_2__ {unsigned long ksp; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int PF_KTHREAD ; 
 scalar_t__ STACK_FRAME_OVERHEAD ; 
 unsigned long THREAD_SIZE ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int
copy_thread(unsigned long clone_flags, unsigned long usp,
	    unsigned long arg, struct task_struct *p)
{
	struct pt_regs *userregs;
	struct pt_regs *kregs;
	unsigned long sp = (unsigned long)task_stack_page(p) + THREAD_SIZE;
	unsigned long top_of_kernel_stack;

	top_of_kernel_stack = sp;

	/* Locate userspace context on stack... */
	sp -= STACK_FRAME_OVERHEAD;	/* redzone */
	sp -= sizeof(struct pt_regs);
	userregs = (struct pt_regs *) sp;

	/* ...and kernel context */
	sp -= STACK_FRAME_OVERHEAD;	/* redzone */
	sp -= sizeof(struct pt_regs);
	kregs = (struct pt_regs *)sp;

	if (unlikely(p->flags & PF_KTHREAD)) {
		memset(kregs, 0, sizeof(struct pt_regs));
		kregs->gpr[20] = usp; /* fn, kernel thread */
		kregs->gpr[22] = arg;
	} else {
		*userregs = *current_pt_regs();

		if (usp)
			userregs->sp = usp;

		/*
		 * For CLONE_SETTLS set "tp" (r10) to the TLS pointer passed to sys_clone.
		 *
		 * The kernel entry is:
		 *	int clone (long flags, void *child_stack, int *parent_tid,
		 *		int *child_tid, struct void *tls)
		 *
		 * This makes the source r7 in the kernel registers.
		 */
		if (clone_flags & CLONE_SETTLS)
			userregs->gpr[10] = userregs->gpr[7];

		userregs->gpr[11] = 0;	/* Result from fork() */

		kregs->gpr[20] = 0;	/* Userspace thread */
	}

	/*
	 * _switch wants the kernel stack page in pt_regs->sp so that it
	 * can restore it to thread_info->ksp... see _switch for details.
	 */
	kregs->sp = top_of_kernel_stack;
	kregs->gpr[9] = (unsigned long)ret_from_fork;

	task_thread_info(p)->ksp = (unsigned long)kregs;

	return 0;
}
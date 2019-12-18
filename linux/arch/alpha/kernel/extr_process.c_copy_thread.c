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
struct TYPE_3__ {unsigned long ksp; int flags; int unique; scalar_t__ usp; } ;
struct thread_info {TYPE_1__ pcb; } ;
struct task_struct {int flags; } ;
struct switch_stack {unsigned long r26; unsigned long r9; unsigned long r10; } ;
struct pt_regs {int r20; scalar_t__ r19; scalar_t__ r0; int /*<<< orphan*/  hae; } ;
struct TYPE_4__ {int /*<<< orphan*/  hae_cache; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int PF_KTHREAD ; 
 TYPE_2__ alpha_mv ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  memset (struct switch_stack*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdusp () ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int
copy_thread(unsigned long clone_flags, unsigned long usp,
	    unsigned long kthread_arg,
	    struct task_struct *p)
{
	extern void ret_from_fork(void);
	extern void ret_from_kernel_thread(void);

	struct thread_info *childti = task_thread_info(p);
	struct pt_regs *childregs = task_pt_regs(p);
	struct pt_regs *regs = current_pt_regs();
	struct switch_stack *childstack, *stack;

	childstack = ((struct switch_stack *) childregs) - 1;
	childti->pcb.ksp = (unsigned long) childstack;
	childti->pcb.flags = 1;	/* set FEN, clear everything else */

	if (unlikely(p->flags & PF_KTHREAD)) {
		/* kernel thread */
		memset(childstack, 0,
			sizeof(struct switch_stack) + sizeof(struct pt_regs));
		childstack->r26 = (unsigned long) ret_from_kernel_thread;
		childstack->r9 = usp;	/* function */
		childstack->r10 = kthread_arg;
		childregs->hae = alpha_mv.hae_cache,
		childti->pcb.usp = 0;
		return 0;
	}
	/* Note: if CLONE_SETTLS is not set, then we must inherit the
	   value from the parent, which will have been set by the block
	   copy in dup_task_struct.  This is non-intuitive, but is
	   required for proper operation in the case of a threaded
	   application calling fork.  */
	if (clone_flags & CLONE_SETTLS)
		childti->pcb.unique = regs->r20;
	else
		regs->r20 = 0;	/* OSF/1 has some strange fork() semantics.  */
	childti->pcb.usp = usp ?: rdusp();
	*childregs = *regs;
	childregs->r0 = 0;
	childregs->r19 = 0;
	childregs->r20 = 1;	/* OSF/1 has some strange fork() semantics.  */
	stack = ((struct switch_stack *) regs) - 1;
	*childstack = *stack;
	childstack->r26 = (unsigned long) ret_from_fork;
	return 0;
}
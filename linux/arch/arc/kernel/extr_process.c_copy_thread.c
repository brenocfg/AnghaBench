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
struct TYPE_3__ {unsigned long ksp; } ;
struct task_struct {unsigned long flags; TYPE_1__ thread; } ;
struct pt_regs {unsigned long sp; int /*<<< orphan*/  user_r25; int /*<<< orphan*/  r3; scalar_t__ r0; } ;
struct callee_regs {unsigned long r13; unsigned long r14; int /*<<< orphan*/  r25; } ;
struct TYPE_4__ {int /*<<< orphan*/  thr_ptr; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 unsigned long PF_KTHREAD ; 
 struct task_struct* current ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 TYPE_2__* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (unsigned long) ; 

int copy_thread(unsigned long clone_flags,
		unsigned long usp, unsigned long kthread_arg,
		struct task_struct *p)
{
	struct pt_regs *c_regs;        /* child's pt_regs */
	unsigned long *childksp;       /* to unwind out of __switch_to() */
	struct callee_regs *c_callee;  /* child's callee regs */
	struct callee_regs *parent_callee;  /* paren't callee */
	struct pt_regs *regs = current_pt_regs();

	/* Mark the specific anchors to begin with (see pic above) */
	c_regs = task_pt_regs(p);
	childksp = (unsigned long *)c_regs - 2;  /* 2 words for FP/BLINK */
	c_callee = ((struct callee_regs *)childksp) - 1;

	/*
	 * __switch_to() uses thread.ksp to start unwinding stack
	 * For kernel threads we don't need to create callee regs, the
	 * stack layout nevertheless needs to remain the same.
	 * Also, since __switch_to anyways unwinds callee regs, we use
	 * this to populate kernel thread entry-pt/args into callee regs,
	 * so that ret_from_kernel_thread() becomes simpler.
	 */
	p->thread.ksp = (unsigned long)c_callee;	/* THREAD_KSP */

	/* __switch_to expects FP(0), BLINK(return addr) at top */
	childksp[0] = 0;			/* fp */
	childksp[1] = (unsigned long)ret_from_fork; /* blink */

	if (unlikely(p->flags & PF_KTHREAD)) {
		memset(c_regs, 0, sizeof(struct pt_regs));

		c_callee->r13 = kthread_arg;
		c_callee->r14 = usp;  /* function */

		return 0;
	}

	/*--------- User Task Only --------------*/

	/* __switch_to expects FP(0), BLINK(return addr) at top of stack */
	childksp[0] = 0;				/* for POP fp */
	childksp[1] = (unsigned long)ret_from_fork;	/* for POP blink */

	/* Copy parents pt regs on child's kernel mode stack */
	*c_regs = *regs;

	if (usp)
		c_regs->sp = usp;

	c_regs->r0 = 0;		/* fork returns 0 in child */

	parent_callee = ((struct callee_regs *)regs) - 1;
	*c_callee = *parent_callee;

	if (unlikely(clone_flags & CLONE_SETTLS)) {
		/*
		 * set task's userland tls data ptr from 4th arg
		 * clone C-lib call is difft from clone sys-call
		 */
		task_thread_info(p)->thr_ptr = regs->r3;
	} else {
		/* Normal fork case: set parent's TLS ptr in child */
		task_thread_info(p)->thr_ptr =
		task_thread_info(current)->thr_ptr;
	}


	/*
	 * setup usermode thread pointer #1:
	 * when child is picked by scheduler, __switch_to() uses @c_callee to
	 * populate usermode callee regs: this works (despite being in a kernel
	 * function) since special return path for child @ret_from_fork()
	 * ensures those regs are not clobbered all the way to RTIE to usermode
	 */
	c_callee->r25 = task_thread_info(p)->thr_ptr;

#ifdef CONFIG_ARC_CURR_IN_REG
	/*
	 * setup usermode thread pointer #2:
	 * however for this special use of r25 in kernel, __switch_to() sets
	 * r25 for kernel needs and only in the final return path is usermode
	 * r25 setup, from pt_regs->user_r25. So set that up as well
	 */
	c_regs->user_r25 = c_callee->r25;
#endif

	return 0;
}
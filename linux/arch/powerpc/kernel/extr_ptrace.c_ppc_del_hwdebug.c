#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ address; scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dbcr0; int /*<<< orphan*/  dbcr1; } ;
struct thread_struct {TYPE_3__ hw_brk; struct perf_event** ptrace_bps; TYPE_2__* regs; TYPE_1__ debug; } ;
struct task_struct {struct thread_struct thread; } ;
struct perf_event {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBCR0_IDM ; 
 int /*<<< orphan*/  DBCR_ACTIVE_EVENTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long EINVAL ; 
 long ENOENT ; 
 int /*<<< orphan*/  MSR_DE ; 
 int del_dac (struct task_struct*,int) ; 
 int del_instruction_bp (struct task_struct*,int) ; 
 int /*<<< orphan*/  unregister_hw_breakpoint (struct perf_event*) ; 

__attribute__((used)) static long ppc_del_hwdebug(struct task_struct *child, long data)
{
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	int ret = 0;
	struct thread_struct *thread = &(child->thread);
	struct perf_event *bp;
#endif /* CONFIG_HAVE_HW_BREAKPOINT */
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
	int rc;

	if (data <= 4)
		rc = del_instruction_bp(child, (int)data);
	else
		rc = del_dac(child, (int)data - 4);

	if (!rc) {
		if (!DBCR_ACTIVE_EVENTS(child->thread.debug.dbcr0,
					child->thread.debug.dbcr1)) {
			child->thread.debug.dbcr0 &= ~DBCR0_IDM;
			child->thread.regs->msr &= ~MSR_DE;
		}
	}
	return rc;
#else
	if (data != 1)
		return -EINVAL;

#ifdef CONFIG_HAVE_HW_BREAKPOINT
	bp = thread->ptrace_bps[0];
	if (bp) {
		unregister_hw_breakpoint(bp);
		thread->ptrace_bps[0] = NULL;
	} else
		ret = -ENOENT;
	return ret;
#else /* CONFIG_HAVE_HW_BREAKPOINT */
	if (child->thread.hw_brk.address == 0)
		return -ENOENT;

	child->thread.hw_brk.address = 0;
	child->thread.hw_brk.type = 0;
#endif /* CONFIG_HAVE_HW_BREAKPOINT */

	return 0;
#endif
}
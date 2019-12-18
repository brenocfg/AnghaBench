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
struct TYPE_3__ {int dbcr0; int /*<<< orphan*/  dbcr1; } ;
struct TYPE_4__ {TYPE_1__ debug; struct pt_regs* regs; } ;
struct task_struct {TYPE_2__ thread; } ;
struct pt_regs {int msr; } ;

/* Variables and functions */
 int DBCR0_BT ; 
 int DBCR0_IC ; 
 int DBCR0_IDM ; 
 int /*<<< orphan*/  DBCR_ACTIVE_EVENTS (int,int /*<<< orphan*/ ) ; 
 int MSR_BE ; 
 int MSR_DE ; 
 int MSR_SE ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void user_disable_single_step(struct task_struct *task)
{
	struct pt_regs *regs = task->thread.regs;

	if (regs != NULL) {
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
		/*
		 * The logic to disable single stepping should be as
		 * simple as turning off the Instruction Complete flag.
		 * And, after doing so, if all debug flags are off, turn
		 * off DBCR0(IDM) and MSR(DE) .... Torez
		 */
		task->thread.debug.dbcr0 &= ~(DBCR0_IC|DBCR0_BT);
		/*
		 * Test to see if any of the DBCR_ACTIVE_EVENTS bits are set.
		 */
		if (!DBCR_ACTIVE_EVENTS(task->thread.debug.dbcr0,
					task->thread.debug.dbcr1)) {
			/*
			 * All debug events were off.....
			 */
			task->thread.debug.dbcr0 &= ~DBCR0_IDM;
			regs->msr &= ~MSR_DE;
		}
#else
		regs->msr &= ~(MSR_SE | MSR_BE);
#endif
	}
	clear_tsk_thread_flag(task, TIF_SINGLESTEP);
}
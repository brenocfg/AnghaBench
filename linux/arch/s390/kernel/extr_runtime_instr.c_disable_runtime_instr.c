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
struct TYPE_3__ {int /*<<< orphan*/ * ri_cb; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;
struct pt_regs {TYPE_2__ psw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSW_MASK_RI ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_runtime_instr_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  runtime_instr_empty_cb ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static void disable_runtime_instr(void)
{
	struct task_struct *task = current;
	struct pt_regs *regs;

	if (!task->thread.ri_cb)
		return;
	regs = task_pt_regs(task);
	preempt_disable();
	load_runtime_instr_cb(&runtime_instr_empty_cb);
	kfree(task->thread.ri_cb);
	task->thread.ri_cb = NULL;
	preempt_enable();

	/*
	 * Make sure the RI bit is deleted from the PSW. If the user did not
	 * switch off RI before the system call the process will get a
	 * specification exception otherwise.
	 */
	regs->psw.mask &= ~PSW_MASK_RI;
}
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
struct TYPE_2__ {int /*<<< orphan*/  softirq_timer; int /*<<< orphan*/  hardirq_timer; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  guest_timer; int /*<<< orphan*/  user_timer; } ;
struct task_struct {TYPE_1__ thread; int /*<<< orphan*/  pid; } ;
struct pt_regs {int dummy; } ;
struct pcpu {struct lowcore* lowcore; } ;
struct lowcore {unsigned long current_task; scalar_t__ steal_timer; int /*<<< orphan*/  softirq_timer; int /*<<< orphan*/  hardirq_timer; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  guest_timer; int /*<<< orphan*/  user_timer; int /*<<< orphan*/  current_pid; int /*<<< orphan*/  lpp; scalar_t__ kernel_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPP_MAGIC ; 
 scalar_t__ STACK_FRAME_OVERHEAD ; 
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

__attribute__((used)) static void pcpu_attach_task(struct pcpu *pcpu, struct task_struct *tsk)
{
	struct lowcore *lc = pcpu->lowcore;

	lc->kernel_stack = (unsigned long) task_stack_page(tsk)
		+ THREAD_SIZE - STACK_FRAME_OVERHEAD - sizeof(struct pt_regs);
	lc->current_task = (unsigned long) tsk;
	lc->lpp = LPP_MAGIC;
	lc->current_pid = tsk->pid;
	lc->user_timer = tsk->thread.user_timer;
	lc->guest_timer = tsk->thread.guest_timer;
	lc->system_timer = tsk->thread.system_timer;
	lc->hardirq_timer = tsk->thread.hardirq_timer;
	lc->softirq_timer = tsk->thread.softirq_timer;
	lc->steal_timer = 0;
}
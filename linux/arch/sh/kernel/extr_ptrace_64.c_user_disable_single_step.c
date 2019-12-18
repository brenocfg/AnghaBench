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
struct TYPE_2__ {struct pt_regs* uregs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_SSTEP ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void user_disable_single_step(struct task_struct *child)
{
	struct pt_regs *regs = child->thread.uregs;

	regs->sr &= ~SR_SSTEP;

	clear_tsk_thread_flag(child, TIF_SINGLESTEP);
}
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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_regs_spsr_ss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 scalar_t__ test_ti_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void user_fastforward_single_step(struct task_struct *task)
{
	if (test_ti_thread_flag(task_thread_info(task), TIF_SINGLESTEP))
		clear_regs_spsr_ss(task_pt_regs(task));
}
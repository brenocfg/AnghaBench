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

/* Variables and functions */
 int /*<<< orphan*/  clear_fpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/ * last_task_used_math ; 
 int /*<<< orphan*/  save_fpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pt_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlazy_fpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  used_math () ; 

void store_fpu_for_suspend(void)
{
#ifdef CONFIG_LAZY_FPU
	if (last_task_used_math != NULL)
		save_fpu(last_task_used_math);
	last_task_used_math = NULL;
#else
	if (!used_math())
		return;
	unlazy_fpu(current);
#endif
	clear_fpu(task_pt_regs(current));
}
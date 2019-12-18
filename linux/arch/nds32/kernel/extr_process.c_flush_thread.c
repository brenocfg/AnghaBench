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
 int /*<<< orphan*/  clear_used_math () ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/ * last_task_used_math ; 
 int /*<<< orphan*/  task_pt_regs (int /*<<< orphan*/ *) ; 

void flush_thread(void)
{
#if defined(CONFIG_FPU)
	clear_fpu(task_pt_regs(current));
	clear_used_math();
# ifdef CONFIG_LAZY_FPU
	if (last_task_used_math == current)
		last_task_used_math = NULL;
# endif
#endif
}
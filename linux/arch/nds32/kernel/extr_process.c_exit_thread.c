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
 struct task_struct* last_task_used_math ; 

void exit_thread(struct task_struct *tsk)
{
#if defined(CONFIG_FPU) && defined(CONFIG_LAZY_FPU)
	if (last_task_used_math == tsk)
		last_task_used_math = NULL;
#endif
}
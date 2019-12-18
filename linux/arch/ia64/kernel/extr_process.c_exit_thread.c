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
struct TYPE_2__ {int flags; scalar_t__ pfm_context; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int IA64_THREAD_DBG_VALID ; 
 int /*<<< orphan*/  ia64_drop_fpu (struct task_struct*) ; 
 int /*<<< orphan*/  pfm_exit_thread (struct task_struct*) ; 
 int /*<<< orphan*/  pfm_release_debug_registers (struct task_struct*) ; 

void
exit_thread (struct task_struct *tsk)
{

	ia64_drop_fpu(tsk);
#ifdef CONFIG_PERFMON
       /* if needed, stop monitoring and flush state to perfmon context */
	if (tsk->thread.pfm_context)
		pfm_exit_thread(tsk);

	/* free debug register resources */
	if (tsk->thread.flags & IA64_THREAD_DBG_VALID)
		pfm_release_debug_registers(tsk);
#endif
}
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
struct TYPE_2__ {int flags; int /*<<< orphan*/ * dbr; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int IA64_THREAD_DBG_VALID ; 
 int IA64_THREAD_PM_VALID ; 
 unsigned long PFM_CPUINFO_SYST_WIDE ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_load_debug_regs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfm_load_regs (struct task_struct*) ; 
 int /*<<< orphan*/  pfm_syst_info ; 
 int /*<<< orphan*/  pfm_syst_wide_update_task (struct task_struct*,unsigned long,int) ; 

void
ia64_load_extra (struct task_struct *task)
{
#ifdef CONFIG_PERFMON
	unsigned long info;
#endif

	if ((task->thread.flags & IA64_THREAD_DBG_VALID) != 0)
		ia64_load_debug_regs(&task->thread.dbr[0]);

#ifdef CONFIG_PERFMON
	if ((task->thread.flags & IA64_THREAD_PM_VALID) != 0)
		pfm_load_regs(task);

	info = __this_cpu_read(pfm_syst_info);
	if (info & PFM_CPUINFO_SYST_WIDE) 
		pfm_syst_wide_update_task(task, info, 1);
#endif
}
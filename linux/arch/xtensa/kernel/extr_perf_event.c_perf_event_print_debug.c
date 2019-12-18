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
 unsigned int XCHAL_NUM_PERF_COUNTERS ; 
 int /*<<< orphan*/  XTENSA_PMU_PM (unsigned int) ; 
 int /*<<< orphan*/  XTENSA_PMU_PMCTRL (unsigned int) ; 
 int /*<<< orphan*/  XTENSA_PMU_PMG ; 
 int /*<<< orphan*/  XTENSA_PMU_PMSTAT (unsigned int) ; 
 int /*<<< orphan*/  get_er (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void perf_event_print_debug(void)
{
	unsigned long flags;
	unsigned i;

	local_irq_save(flags);
	pr_info("CPU#%d: PMG: 0x%08lx\n", smp_processor_id(),
		get_er(XTENSA_PMU_PMG));
	for (i = 0; i < XCHAL_NUM_PERF_COUNTERS; ++i)
		pr_info("PM%d: 0x%08lx, PMCTRL%d: 0x%08lx, PMSTAT%d: 0x%08lx\n",
			i, get_er(XTENSA_PMU_PM(i)),
			i, get_er(XTENSA_PMU_PMCTRL(i)),
			i, get_er(XTENSA_PMU_PMSTAT(i)));
	local_irq_restore(flags);
}
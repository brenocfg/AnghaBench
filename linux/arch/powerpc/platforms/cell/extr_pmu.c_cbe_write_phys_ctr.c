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
typedef  size_t u32 ;
struct cbe_pmd_shadow_regs {int counter_value_in_latch; } ;

/* Variables and functions */
 size_t CBE_PM_ENABLE_PERF_MON ; 
 size_t NR_PHYS_CTRS ; 
 int /*<<< orphan*/  WRITE_WO_MMIO (int /*<<< orphan*/ ,size_t) ; 
 struct cbe_pmd_shadow_regs* cbe_get_cpu_pmd_shadow_regs (size_t) ; 
 size_t cbe_read_pm (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbe_write_pm (size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pm_control ; 
 int /*<<< orphan*/ * pm_ctr ; 

void cbe_write_phys_ctr(u32 cpu, u32 phys_ctr, u32 val)
{
	struct cbe_pmd_shadow_regs *shadow_regs;
	u32 pm_ctrl;

	if (phys_ctr < NR_PHYS_CTRS) {
		/* Writing to a counter only writes to a hardware latch.
		 * The new value is not propagated to the actual counter
		 * until the performance monitor is enabled.
		 */
		WRITE_WO_MMIO(pm_ctr[phys_ctr], val);

		pm_ctrl = cbe_read_pm(cpu, pm_control);
		if (pm_ctrl & CBE_PM_ENABLE_PERF_MON) {
			/* The counters are already active, so we need to
			 * rewrite the pm_control register to "re-enable"
			 * the PMU.
			 */
			cbe_write_pm(cpu, pm_control, pm_ctrl);
		} else {
			shadow_regs = cbe_get_cpu_pmd_shadow_regs(cpu);
			shadow_regs->counter_value_in_latch |= (1 << phys_ctr);
		}
	}
}
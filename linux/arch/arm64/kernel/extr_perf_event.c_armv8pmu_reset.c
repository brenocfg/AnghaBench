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
typedef  scalar_t__ u32 ;
struct arm_pmu {scalar_t__ num_events; } ;

/* Variables and functions */
 scalar_t__ ARMV8_IDX_CYCLE_COUNTER ; 
 int ARMV8_PMU_PMCR_C ; 
 int ARMV8_PMU_PMCR_LC ; 
 int ARMV8_PMU_PMCR_P ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  armv8pmu_disable_counter (scalar_t__) ; 
 int /*<<< orphan*/  armv8pmu_disable_intens (scalar_t__) ; 
 int /*<<< orphan*/  armv8pmu_pmcr_write (int) ; 
 int /*<<< orphan*/  kvm_clr_pmu_events (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armv8pmu_reset(void *info)
{
	struct arm_pmu *cpu_pmu = (struct arm_pmu *)info;
	u32 idx, nb_cnt = cpu_pmu->num_events;

	/* The counter and interrupt enable registers are unknown at reset. */
	for (idx = ARMV8_IDX_CYCLE_COUNTER; idx < nb_cnt; ++idx) {
		armv8pmu_disable_counter(idx);
		armv8pmu_disable_intens(idx);
	}

	/* Clear the counters we flip at guest entry/exit */
	kvm_clr_pmu_events(U32_MAX);

	/*
	 * Initialize & Reset PMNC. Request overflow interrupt for
	 * 64 bit cycle counter but cheat in armv8pmu_write_counter().
	 */
	armv8pmu_pmcr_write(ARMV8_PMU_PMCR_P | ARMV8_PMU_PMCR_C |
			    ARMV8_PMU_PMCR_LC);
}
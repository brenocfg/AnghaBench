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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
#define  ARMV8_PMU_CYCLE_IDX 128 
 int /*<<< orphan*/  PMEVTYPER_CASES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pmccfiltr_el0 ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 kvm_vcpu_pmu_read_evtype_direct(int idx)
{
	switch (idx) {
	PMEVTYPER_CASES(READ);
	case ARMV8_PMU_CYCLE_IDX:
		return read_sysreg(pmccfiltr_el0);
	default:
		WARN_ON(1);
	}

	return 0;
}
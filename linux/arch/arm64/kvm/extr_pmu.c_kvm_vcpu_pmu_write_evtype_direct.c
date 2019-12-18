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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  ARMV8_PMU_CYCLE_IDX 128 
 int /*<<< orphan*/  PMEVTYPER_CASES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  pmccfiltr_el0 ; 
 int /*<<< orphan*/  write_sysreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vcpu_pmu_write_evtype_direct(int idx, u32 val)
{
	switch (idx) {
	PMEVTYPER_CASES(WRITE);
	case ARMV8_PMU_CYCLE_IDX:
		write_sysreg(val, pmccfiltr_el0);
		break;
	default:
		WARN_ON(1);
	}
}
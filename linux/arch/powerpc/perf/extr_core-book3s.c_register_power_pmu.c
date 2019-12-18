#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct power_pmu {int /*<<< orphan*/  attr_groups; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_PERF_POWER ; 
 int EBUSY ; 
 int /*<<< orphan*/  MMCR0_FCHV ; 
 int MSR_HV ; 
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeze_events_kernel ; 
 int mfmsr () ; 
 int /*<<< orphan*/  perf_pmu_register (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ power_pmu ; 
 int /*<<< orphan*/  power_pmu_prepare_cpu ; 
 struct power_pmu* ppmu ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int register_power_pmu(struct power_pmu *pmu)
{
	if (ppmu)
		return -EBUSY;		/* something's already registered */

	ppmu = pmu;
	pr_info("%s performance monitor hardware support registered\n",
		pmu->name);

	power_pmu.attr_groups = ppmu->attr_groups;

#ifdef MSR_HV
	/*
	 * Use FCHV to ignore kernel events if MSR.HV is set.
	 */
	if (mfmsr() & MSR_HV)
		freeze_events_kernel = MMCR0_FCHV;
#endif /* CONFIG_PPC64 */

	perf_pmu_register(&power_pmu, "cpu", PERF_TYPE_RAW);
	cpuhp_setup_state(CPUHP_PERF_POWER, "perf/powerpc:prepare",
			  power_pmu_prepare_cpu, NULL);
	return 0;
}
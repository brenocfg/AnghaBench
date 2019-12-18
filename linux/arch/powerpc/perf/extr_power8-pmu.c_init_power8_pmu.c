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
struct TYPE_2__ {int /*<<< orphan*/  cpu_user_features2; int /*<<< orphan*/  oprofile_cpu_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_PMAO_BUG ; 
 int ENODEV ; 
 int /*<<< orphan*/  PPC_FEATURE2_EBB ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__* cur_cpu_spec ; 
 int /*<<< orphan*/  power8_pmu ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int register_power_pmu (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int init_power8_pmu(void)
{
	int rc;

	if (!cur_cpu_spec->oprofile_cpu_type ||
	    strcmp(cur_cpu_spec->oprofile_cpu_type, "ppc64/power8"))
		return -ENODEV;

	rc = register_power_pmu(&power8_pmu);
	if (rc)
		return rc;

	/* Tell userspace that EBB is supported */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_EBB;

	if (cpu_has_feature(CPU_FTR_PMAO_BUG))
		pr_info("PMAO restore workaround active.\n");

	return 0;
}
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
struct TYPE_2__ {int /*<<< orphan*/  cpu_user_features2; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_FEATURE2_EBB ; 
 TYPE_1__* cur_cpu_spec ; 
 int /*<<< orphan*/  generic_compat_pmu ; 
 int register_power_pmu (int /*<<< orphan*/ *) ; 

int init_generic_compat_pmu(void)
{
	int rc = 0;

	rc = register_power_pmu(&generic_compat_pmu);
	if (rc)
		return rc;

	/* Tell userspace that EBB is supported */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_EBB;

	return 0;
}
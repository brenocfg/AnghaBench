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
struct arm_pmu {char* name; int /*<<< orphan*/ ** attr_groups; int /*<<< orphan*/  map_event; } ;

/* Variables and functions */
 size_t ARMPMU_ATTR_GROUP_EVENTS ; 
 size_t ARMPMU_ATTR_GROUP_FORMATS ; 
 int /*<<< orphan*/  armv8_a73_map_event ; 
 int armv8_pmu_init (struct arm_pmu*) ; 
 int /*<<< orphan*/  armv8_pmuv3_events_attr_group ; 
 int /*<<< orphan*/  armv8_pmuv3_format_attr_group ; 

__attribute__((used)) static int armv8_a73_pmu_init(struct arm_pmu *cpu_pmu)
{
	int ret = armv8_pmu_init(cpu_pmu);
	if (ret)
		return ret;

	cpu_pmu->name			= "armv8_cortex_a73";
	cpu_pmu->map_event		= armv8_a73_map_event;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv8_pmuv3_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv8_pmuv3_format_attr_group;

	return 0;
}
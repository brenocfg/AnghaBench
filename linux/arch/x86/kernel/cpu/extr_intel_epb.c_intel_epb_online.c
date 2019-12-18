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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_tasks_frozen ; 
 struct device* get_cpu_device (unsigned int) ; 
 int /*<<< orphan*/  intel_epb_attr_group ; 
 int /*<<< orphan*/  intel_epb_restore () ; 
 int /*<<< orphan*/  sysfs_merge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_epb_online(unsigned int cpu)
{
	struct device *cpu_dev = get_cpu_device(cpu);

	intel_epb_restore();
	if (!cpuhp_tasks_frozen)
		sysfs_merge_group(&cpu_dev->kobj, &intel_epb_attr_group);

	return 0;
}
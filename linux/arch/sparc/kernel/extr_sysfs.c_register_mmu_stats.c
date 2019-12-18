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
 int /*<<< orphan*/  dev_attr_mmustat_enable ; 
 int /*<<< orphan*/  device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_stat_group ; 
 int /*<<< orphan*/  mmu_stats_supported ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_mmu_stats(struct device *s)
{
	if (!mmu_stats_supported)
		return 0;
	device_create_file(s, &dev_attr_mmustat_enable);
	return sysfs_create_group(&s->kobj, &mmu_stat_group);
}
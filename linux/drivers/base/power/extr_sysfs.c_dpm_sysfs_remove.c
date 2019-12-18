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
 int /*<<< orphan*/  dev_pm_qos_constraints_destroy (struct device*) ; 
 scalar_t__ device_pm_not_required (struct device*) ; 
 int /*<<< orphan*/  pm_attr_group ; 
 int /*<<< orphan*/  pm_qos_latency_tolerance_attr_group ; 
 int /*<<< orphan*/  pm_wakeup_attr_group ; 
 int /*<<< orphan*/  rpm_sysfs_remove (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_unmerge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dpm_sysfs_remove(struct device *dev)
{
	if (device_pm_not_required(dev))
		return;
	sysfs_unmerge_group(&dev->kobj, &pm_qos_latency_tolerance_attr_group);
	dev_pm_qos_constraints_destroy(dev);
	rpm_sysfs_remove(dev);
	sysfs_unmerge_group(&dev->kobj, &pm_wakeup_attr_group);
	sysfs_remove_group(&dev->kobj, &pm_attr_group);
}
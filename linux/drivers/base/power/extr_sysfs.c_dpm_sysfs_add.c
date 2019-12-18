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
struct TYPE_2__ {scalar_t__ set_latency_tolerance; } ;
struct device {int /*<<< orphan*/  kobj; TYPE_1__ power; } ;

/* Variables and functions */
 scalar_t__ device_can_wakeup (struct device*) ; 
 scalar_t__ device_pm_not_required (struct device*) ; 
 int /*<<< orphan*/  pm_attr_group ; 
 int /*<<< orphan*/  pm_qos_latency_tolerance_attr_group ; 
 int /*<<< orphan*/  pm_runtime_attr_group ; 
 scalar_t__ pm_runtime_callbacks_present (struct device*) ; 
 int /*<<< orphan*/  pm_wakeup_attr_group ; 
 int pm_wakeup_source_sysfs_add (struct device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_merge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_unmerge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int dpm_sysfs_add(struct device *dev)
{
	int rc;

	/* No need to create PM sysfs if explicitly disabled. */
	if (device_pm_not_required(dev))
		return 0;

	rc = sysfs_create_group(&dev->kobj, &pm_attr_group);
	if (rc)
		return rc;

	if (pm_runtime_callbacks_present(dev)) {
		rc = sysfs_merge_group(&dev->kobj, &pm_runtime_attr_group);
		if (rc)
			goto err_out;
	}
	if (device_can_wakeup(dev)) {
		rc = sysfs_merge_group(&dev->kobj, &pm_wakeup_attr_group);
		if (rc)
			goto err_runtime;
	}
	if (dev->power.set_latency_tolerance) {
		rc = sysfs_merge_group(&dev->kobj,
				       &pm_qos_latency_tolerance_attr_group);
		if (rc)
			goto err_wakeup;
	}
	rc = pm_wakeup_source_sysfs_add(dev);
	if (rc)
		goto err_latency;
	return 0;

 err_latency:
	sysfs_unmerge_group(&dev->kobj, &pm_qos_latency_tolerance_attr_group);
 err_wakeup:
	sysfs_unmerge_group(&dev->kobj, &pm_wakeup_attr_group);
 err_runtime:
	sysfs_unmerge_group(&dev->kobj, &pm_runtime_attr_group);
 err_out:
	sysfs_remove_group(&dev->kobj, &pm_attr_group);
	return rc;
}
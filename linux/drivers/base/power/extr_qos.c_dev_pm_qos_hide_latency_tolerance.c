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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT ; 
 int /*<<< orphan*/  dev_pm_qos_sysfs_mtx ; 
 int /*<<< orphan*/  dev_pm_qos_update_user_latency_tolerance (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_sysfs_remove_latency_tolerance (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

void dev_pm_qos_hide_latency_tolerance(struct device *dev)
{
	mutex_lock(&dev_pm_qos_sysfs_mtx);
	pm_qos_sysfs_remove_latency_tolerance(dev);
	mutex_unlock(&dev_pm_qos_sysfs_mtx);

	/* Remove the request from user space now */
	pm_runtime_get_sync(dev);
	dev_pm_qos_update_user_latency_tolerance(dev,
		PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT);
	pm_runtime_put(dev);
}
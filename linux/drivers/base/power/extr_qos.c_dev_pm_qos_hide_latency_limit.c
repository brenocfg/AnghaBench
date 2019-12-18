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
 int /*<<< orphan*/  __dev_pm_qos_hide_latency_limit (struct device*) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  dev_pm_qos_sysfs_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_sysfs_remove_resume_latency (struct device*) ; 

void dev_pm_qos_hide_latency_limit(struct device *dev)
{
	mutex_lock(&dev_pm_qos_sysfs_mtx);

	pm_qos_sysfs_remove_resume_latency(dev);

	mutex_lock(&dev_pm_qos_mtx);
	__dev_pm_qos_hide_latency_limit(dev);
	mutex_unlock(&dev_pm_qos_mtx);

	mutex_unlock(&dev_pm_qos_sysfs_mtx);
}
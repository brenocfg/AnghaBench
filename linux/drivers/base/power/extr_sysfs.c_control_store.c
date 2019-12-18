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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  ctrl_auto ; 
 int /*<<< orphan*/  ctrl_on ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_allow (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t control_store(struct device * dev, struct device_attribute *attr,
			     const char * buf, size_t n)
{
	device_lock(dev);
	if (sysfs_streq(buf, ctrl_auto))
		pm_runtime_allow(dev);
	else if (sysfs_streq(buf, ctrl_on))
		pm_runtime_forbid(dev);
	else
		n = -EINVAL;
	device_unlock(dev);
	return n;
}
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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned long check_interval ; 
 int /*<<< orphan*/  device_store_ulong (struct device*,struct device_attribute*,char const*,size_t) ; 
 int /*<<< orphan*/  mce_restart () ; 
 int /*<<< orphan*/  mce_sysfs_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_int_with_restart(struct device *s,
				      struct device_attribute *attr,
				      const char *buf, size_t size)
{
	unsigned long old_check_interval = check_interval;
	ssize_t ret = device_store_ulong(s, attr, buf, size);

	if (check_interval == old_check_interval)
		return ret;

	mutex_lock(&mce_sysfs_mutex);
	mce_restart();
	mutex_unlock(&mce_sysfs_mutex);

	return ret;
}
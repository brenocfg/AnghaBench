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
typedef  scalar_t__ u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int ignore_ce; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtou64 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  mce_disable_cmci ; 
 int /*<<< orphan*/  mce_enable_ce ; 
 int /*<<< orphan*/  mce_sysfs_mutex ; 
 int /*<<< orphan*/  mce_timer_delete_all () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static ssize_t set_ignore_ce(struct device *s,
			     struct device_attribute *attr,
			     const char *buf, size_t size)
{
	u64 new;

	if (kstrtou64(buf, 0, &new) < 0)
		return -EINVAL;

	mutex_lock(&mce_sysfs_mutex);
	if (mca_cfg.ignore_ce ^ !!new) {
		if (new) {
			/* disable ce features */
			mce_timer_delete_all();
			on_each_cpu(mce_disable_cmci, NULL, 1);
			mca_cfg.ignore_ce = true;
		} else {
			/* enable ce features */
			mca_cfg.ignore_ce = false;
			on_each_cpu(mce_enable_ce, (void *)1, 1);
		}
	}
	mutex_unlock(&mce_sysfs_mutex);

	return size;
}
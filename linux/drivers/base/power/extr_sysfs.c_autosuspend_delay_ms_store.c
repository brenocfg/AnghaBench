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
struct device_attribute {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_autosuspend; } ;
struct device {TYPE_1__ power; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,long) ; 

__attribute__((used)) static ssize_t autosuspend_delay_ms_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t n)
{
	long delay;

	if (!dev->power.use_autosuspend)
		return -EIO;

	if (kstrtol(buf, 10, &delay) != 0 || delay != (int) delay)
		return -EINVAL;

	device_lock(dev);
	pm_runtime_set_autosuspend_delay(dev, delay);
	device_unlock(dev);
	return n;
}
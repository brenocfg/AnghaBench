#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct TYPE_3__ {TYPE_2__* qos; } ;
struct device {TYPE_1__ power; } ;
typedef  int ssize_t ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int /*<<< orphan*/  resume_latency_req; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PM_QOS_RESUME_LATENCY_NO_CONSTRAINT ; 
 int dev_pm_qos_update_request (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kstrtos32 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t pm_qos_resume_latency_us_store(struct device *dev,
					      struct device_attribute *attr,
					      const char *buf, size_t n)
{
	s32 value;
	int ret;

	if (!kstrtos32(buf, 0, &value)) {
		/*
		 * Prevent users from writing negative or "no constraint" values
		 * directly.
		 */
		if (value < 0 || value == PM_QOS_RESUME_LATENCY_NO_CONSTRAINT)
			return -EINVAL;

		if (value == 0)
			value = PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
	} else if (sysfs_streq(buf, "n/a")) {
		value = 0;
	} else {
		return -EINVAL;
	}

	ret = dev_pm_qos_update_request(dev->power.qos->resume_latency_req,
					value);
	return ret < 0 ? ret : n;
}
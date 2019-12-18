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
struct TYPE_2__ {scalar_t__ disable_depth; scalar_t__ runtime_status; scalar_t__ request; scalar_t__ request_pending; scalar_t__ deferred_resume; int /*<<< orphan*/  child_count; int /*<<< orphan*/  ignore_children; int /*<<< orphan*/  usage_count; scalar_t__ runtime_error; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ RPM_REQ_RESUME ; 
 scalar_t__ RPM_SUSPENDED ; 
 scalar_t__ RPM_SUSPENDING ; 
 scalar_t__ __dev_pm_qos_resume_latency (struct device*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpm_check_suspend_allowed(struct device *dev)
{
	int retval = 0;

	if (dev->power.runtime_error)
		retval = -EINVAL;
	else if (dev->power.disable_depth > 0)
		retval = -EACCES;
	else if (atomic_read(&dev->power.usage_count) > 0)
		retval = -EAGAIN;
	else if (!dev->power.ignore_children &&
			atomic_read(&dev->power.child_count))
		retval = -EBUSY;

	/* Pending resume requests take precedence over suspends. */
	else if ((dev->power.deferred_resume
			&& dev->power.runtime_status == RPM_SUSPENDING)
	    || (dev->power.request_pending
			&& dev->power.request == RPM_REQ_RESUME))
		retval = -EAGAIN;
	else if (__dev_pm_qos_resume_latency(dev) == 0)
		retval = -EPERM;
	else if (dev->power.runtime_status == RPM_SUSPENDED)
		retval = 1;

	return retval;
}
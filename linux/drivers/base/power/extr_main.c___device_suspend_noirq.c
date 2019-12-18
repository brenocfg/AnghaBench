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
struct TYPE_4__ {int is_noirq_suspended; int must_resume; int /*<<< orphan*/  completion; int /*<<< orphan*/  usage_count; scalar_t__ direct_complete; scalar_t__ syscore; } ;
struct device {TYPE_2__ power; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  scalar_t__ pm_callback_t ;
struct TYPE_3__ {scalar_t__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_FLAG_LEAVE_SUSPENDED ; 
 int /*<<< orphan*/  TRACE_DEVICE (struct device*) ; 
 int /*<<< orphan*/  TRACE_SUSPEND (int) ; 
 int async_error ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 scalar_t__ dev_pm_smart_suspend_and_suspended (struct device*) ; 
 scalar_t__ dev_pm_test_driver_flags (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_must_resume (struct device*,int /*<<< orphan*/ ,int) ; 
 int dpm_run_callback (scalar_t__,struct device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dpm_subsys_suspend_late_cb (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dpm_subsys_suspend_noirq_cb (struct device*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  dpm_superior_set_must_resume (struct device*) ; 
 int /*<<< orphan*/  dpm_wait_for_subordinate (struct device*,int) ; 
 scalar_t__ pm_noirq_op (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __device_suspend_noirq(struct device *dev, pm_message_t state, bool async)
{
	pm_callback_t callback;
	const char *info;
	bool no_subsys_cb = false;
	int error = 0;

	TRACE_DEVICE(dev);
	TRACE_SUSPEND(0);

	dpm_wait_for_subordinate(dev, async);

	if (async_error)
		goto Complete;

	if (dev->power.syscore || dev->power.direct_complete)
		goto Complete;

	callback = dpm_subsys_suspend_noirq_cb(dev, state, &info);
	if (callback)
		goto Run;

	no_subsys_cb = !dpm_subsys_suspend_late_cb(dev, state, NULL);

	if (dev_pm_smart_suspend_and_suspended(dev) && no_subsys_cb)
		goto Skip;

	if (dev->driver && dev->driver->pm) {
		info = "noirq driver ";
		callback = pm_noirq_op(dev->driver->pm, state);
	}

Run:
	error = dpm_run_callback(callback, dev, state, info);
	if (error) {
		async_error = error;
		goto Complete;
	}

Skip:
	dev->power.is_noirq_suspended = true;

	if (dev_pm_test_driver_flags(dev, DPM_FLAG_LEAVE_SUSPENDED)) {
		dev->power.must_resume = dev->power.must_resume ||
				atomic_read(&dev->power.usage_count) > 1 ||
				device_must_resume(dev, state, no_subsys_cb);
	} else {
		dev->power.must_resume = true;
	}

	if (dev->power.must_resume)
		dpm_superior_set_must_resume(dev);

Complete:
	complete_all(&dev->power.completion);
	TRACE_SUSPEND(error);
	return error;
}
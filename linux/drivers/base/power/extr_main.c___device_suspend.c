#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int direct_complete; int wakeup_path; int may_skip_resume; int must_resume; int is_suspended; int /*<<< orphan*/  completion; scalar_t__ syscore; } ;
struct device {TYPE_6__ power; TYPE_5__* driver; TYPE_4__* bus; TYPE_3__* class; TYPE_2__* type; TYPE_1__* pm_domain; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  int /*<<< orphan*/ * pm_callback_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_10__ {scalar_t__ suspend; int /*<<< orphan*/ * pm; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_7__ {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_DPM_WATCHDOG_ON_STACK (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  TRACE_DEVICE (struct device*) ; 
 int /*<<< orphan*/  TRACE_SUSPEND (int) ; 
 int async_error ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  dpm_clear_superiors_direct_complete (struct device*) ; 
 int /*<<< orphan*/  dpm_propagate_wakeup_to_parent (struct device*) ; 
 int dpm_run_callback (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dpm_wait_for_subordinate (struct device*,int) ; 
 int /*<<< orphan*/  dpm_watchdog_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpm_watchdog_set (int /*<<< orphan*/ *,struct device*) ; 
 int legacy_suspend (struct device*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  pm_dev_dbg (struct device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pm_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_barrier (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 scalar_t__ pm_runtime_status_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_wakeup_event (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_wakeup_pending () ; 
 int /*<<< orphan*/  wd ; 

__attribute__((used)) static int __device_suspend(struct device *dev, pm_message_t state, bool async)
{
	pm_callback_t callback = NULL;
	const char *info = NULL;
	int error = 0;
	DECLARE_DPM_WATCHDOG_ON_STACK(wd);

	TRACE_DEVICE(dev);
	TRACE_SUSPEND(0);

	dpm_wait_for_subordinate(dev, async);

	if (async_error) {
		dev->power.direct_complete = false;
		goto Complete;
	}

	/*
	 * If a device configured to wake up the system from sleep states
	 * has been suspended at run time and there's a resume request pending
	 * for it, this is equivalent to the device signaling wakeup, so the
	 * system suspend operation should be aborted.
	 */
	if (pm_runtime_barrier(dev) && device_may_wakeup(dev))
		pm_wakeup_event(dev, 0);

	if (pm_wakeup_pending()) {
		dev->power.direct_complete = false;
		async_error = -EBUSY;
		goto Complete;
	}

	if (dev->power.syscore)
		goto Complete;

	/* Avoid direct_complete to let wakeup_path propagate. */
	if (device_may_wakeup(dev) || dev->power.wakeup_path)
		dev->power.direct_complete = false;

	if (dev->power.direct_complete) {
		if (pm_runtime_status_suspended(dev)) {
			pm_runtime_disable(dev);
			if (pm_runtime_status_suspended(dev)) {
				pm_dev_dbg(dev, state, "direct-complete ");
				goto Complete;
			}

			pm_runtime_enable(dev);
		}
		dev->power.direct_complete = false;
	}

	dev->power.may_skip_resume = false;
	dev->power.must_resume = false;

	dpm_watchdog_set(&wd, dev);
	device_lock(dev);

	if (dev->pm_domain) {
		info = "power domain ";
		callback = pm_op(&dev->pm_domain->ops, state);
		goto Run;
	}

	if (dev->type && dev->type->pm) {
		info = "type ";
		callback = pm_op(dev->type->pm, state);
		goto Run;
	}

	if (dev->class && dev->class->pm) {
		info = "class ";
		callback = pm_op(dev->class->pm, state);
		goto Run;
	}

	if (dev->bus) {
		if (dev->bus->pm) {
			info = "bus ";
			callback = pm_op(dev->bus->pm, state);
		} else if (dev->bus->suspend) {
			pm_dev_dbg(dev, state, "legacy bus ");
			error = legacy_suspend(dev, state, dev->bus->suspend,
						"legacy bus ");
			goto End;
		}
	}

 Run:
	if (!callback && dev->driver && dev->driver->pm) {
		info = "driver ";
		callback = pm_op(dev->driver->pm, state);
	}

	error = dpm_run_callback(callback, dev, state, info);

 End:
	if (!error) {
		dev->power.is_suspended = true;
		if (device_may_wakeup(dev))
			dev->power.wakeup_path = true;

		dpm_propagate_wakeup_to_parent(dev);
		dpm_clear_superiors_direct_complete(dev);
	}

	device_unlock(dev);
	dpm_watchdog_clear(&wd);

 Complete:
	if (error)
		async_error = error;

	complete_all(&dev->power.completion);
	TRACE_SUSPEND(error);
	return error;
}
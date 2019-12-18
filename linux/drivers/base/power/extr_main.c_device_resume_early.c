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
struct TYPE_4__ {int is_late_suspended; int /*<<< orphan*/  completion; scalar_t__ direct_complete; scalar_t__ syscore; } ;
struct device {TYPE_2__ power; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  scalar_t__ pm_callback_t ;
struct TYPE_3__ {scalar_t__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_DEVICE (struct device*) ; 
 int /*<<< orphan*/  TRACE_RESUME (int) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int dpm_run_callback (scalar_t__,struct device*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dpm_subsys_resume_early_cb (struct device*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  dpm_wait_for_superior (struct device*,int) ; 
 scalar_t__ pm_late_early_op (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 

__attribute__((used)) static int device_resume_early(struct device *dev, pm_message_t state, bool async)
{
	pm_callback_t callback;
	const char *info;
	int error = 0;

	TRACE_DEVICE(dev);
	TRACE_RESUME(0);

	if (dev->power.syscore || dev->power.direct_complete)
		goto Out;

	if (!dev->power.is_late_suspended)
		goto Out;

	dpm_wait_for_superior(dev, async);

	callback = dpm_subsys_resume_early_cb(dev, state, &info);

	if (!callback && dev->driver && dev->driver->pm) {
		info = "early driver ";
		callback = pm_late_early_op(dev->driver->pm, state);
	}

	error = dpm_run_callback(callback, dev, state, info);
	dev->power.is_late_suspended = false;

 Out:
	TRACE_RESUME(error);

	pm_runtime_enable(dev);
	complete_all(&dev->power.completion);
	return error;
}
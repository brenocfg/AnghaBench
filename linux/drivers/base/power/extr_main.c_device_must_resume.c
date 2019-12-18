#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  may_skip_resume; } ;
struct device {TYPE_1__ power; } ;
struct TYPE_10__ {scalar_t__ event; } ;
typedef  TYPE_2__ pm_message_t ;

/* Variables and functions */
 scalar_t__ PM_EVENT_RESUME ; 
 scalar_t__ device_can_wakeup (struct device*) ; 
 int /*<<< orphan*/  device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  dpm_subsys_resume_early_cb (struct device*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpm_subsys_resume_noirq_cb (struct device*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpm_subsys_suspend_late_cb (struct device*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (struct device*) ; 
 TYPE_2__ resume_event (TYPE_2__) ; 

__attribute__((used)) static bool device_must_resume(struct device *dev, pm_message_t state,
			       bool no_subsys_suspend_noirq)
{
	pm_message_t resume_msg = resume_event(state);

	/*
	 * If all of the device driver's "noirq", "late" and "early" callbacks
	 * are invoked directly by the core, the decision to allow the device to
	 * stay in suspend can be based on its current runtime PM status and its
	 * wakeup settings.
	 */
	if (no_subsys_suspend_noirq &&
	    !dpm_subsys_suspend_late_cb(dev, state, NULL) &&
	    !dpm_subsys_resume_early_cb(dev, resume_msg, NULL) &&
	    !dpm_subsys_resume_noirq_cb(dev, resume_msg, NULL))
		return !pm_runtime_status_suspended(dev) &&
			(resume_msg.event != PM_EVENT_RESUME ||
			 (device_can_wakeup(dev) && !device_may_wakeup(dev)));

	/*
	 * The only safe strategy here is to require that if the device may not
	 * be left in suspend, resume callbacks must be invoked for it.
	 */
	return !dev->power.may_skip_resume;
}
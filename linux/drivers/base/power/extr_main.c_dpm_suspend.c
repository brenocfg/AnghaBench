#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  prev; } ;
struct TYPE_11__ {TYPE_6__ entry; } ;
struct device {TYPE_1__ power; } ;
struct TYPE_12__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ pm_message_t ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_13__ {int /*<<< orphan*/  failed_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND_SUSPEND ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int async_error ; 
 int /*<<< orphan*/  async_synchronize_full () ; 
 int /*<<< orphan*/  cpufreq_suspend () ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devfreq_suspend () ; 
 int device_suspend (struct device*) ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 TYPE_6__ dpm_prepared_list ; 
 int /*<<< orphan*/  dpm_save_failed_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_save_failed_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_show_time (int /*<<< orphan*/ ,TYPE_2__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpm_suspended_list ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  list_empty (TYPE_6__*) ; 
 int /*<<< orphan*/  list_move (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_dev_err (struct device*,TYPE_2__,char*,int) ; 
 TYPE_2__ pm_transition ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 TYPE_3__ suspend_stats ; 
 struct device* to_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dpm_suspend(pm_message_t state)
{
	ktime_t starttime = ktime_get();
	int error = 0;

	trace_suspend_resume(TPS("dpm_suspend"), state.event, true);
	might_sleep();

	devfreq_suspend();
	cpufreq_suspend();

	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;
	while (!list_empty(&dpm_prepared_list)) {
		struct device *dev = to_device(dpm_prepared_list.prev);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend(dev);

		mutex_lock(&dpm_list_mtx);
		if (error) {
			pm_dev_err(dev, state, "", error);
			dpm_save_failed_dev(dev_name(dev));
			put_device(dev);
			break;
		}
		if (!list_empty(&dev->power.entry))
			list_move(&dev->power.entry, &dpm_suspended_list);
		put_device(dev);
		if (async_error)
			break;
	}
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	if (!error)
		error = async_error;
	if (error) {
		suspend_stats.failed_suspend++;
		dpm_save_failed_step(SUSPEND_SUSPEND);
	}
	dpm_show_time(starttime, state, error, NULL);
	trace_suspend_resume(TPS("dpm_suspend"), state.event, false);
	return error;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  next; } ;
struct TYPE_8__ {int is_prepared; TYPE_3__ entry; } ;
struct device {TYPE_1__ power; } ;
struct TYPE_9__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ pm_message_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_block_probing () ; 
 int device_prepare (struct device*,TYPE_2__) ; 
 TYPE_3__ dpm_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 int /*<<< orphan*/  dpm_prepared_list ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  list_move_tail (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* to_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_device_pm_callback_end (struct device*,int) ; 
 int /*<<< orphan*/  trace_device_pm_callback_start (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_device_probe () ; 

int dpm_prepare(pm_message_t state)
{
	int error = 0;

	trace_suspend_resume(TPS("dpm_prepare"), state.event, true);
	might_sleep();

	/*
	 * Give a chance for the known devices to complete their probes, before
	 * disable probing of devices. This sync point is important at least
	 * at boot time + hibernation restore.
	 */
	wait_for_device_probe();
	/*
	 * It is unsafe if probing of devices will happen during suspend or
	 * hibernation and system behavior will be unpredictable in this case.
	 * So, let's prohibit device's probing here and defer their probes
	 * instead. The normal behavior will be restored in dpm_complete().
	 */
	device_block_probing();

	mutex_lock(&dpm_list_mtx);
	while (!list_empty(&dpm_list)) {
		struct device *dev = to_device(dpm_list.next);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		trace_device_pm_callback_start(dev, "", state.event);
		error = device_prepare(dev, state);
		trace_device_pm_callback_end(dev, error);

		mutex_lock(&dpm_list_mtx);
		if (error) {
			if (error == -EAGAIN) {
				put_device(dev);
				error = 0;
				continue;
			}
			pr_info("Device %s not prepared for power transition: code %d\n",
				dev_name(dev), error);
			put_device(dev);
			break;
		}
		dev->power.is_prepared = true;
		if (!list_empty(&dev->power.entry))
			list_move_tail(&dev->power.entry, &dpm_prepared_list);
		put_device(dev);
	}
	mutex_unlock(&dpm_list_mtx);
	trace_suspend_resume(TPS("dpm_prepare"), state.event, false);
	return error;
}
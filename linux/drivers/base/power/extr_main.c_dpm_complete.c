#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_7__ {int is_prepared; int /*<<< orphan*/  entry; } ;
struct device {TYPE_1__ power; } ;
struct TYPE_8__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ pm_message_t ;
struct TYPE_9__ {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  device_complete (struct device*,TYPE_2__) ; 
 int /*<<< orphan*/  device_unblock_probing () ; 
 int /*<<< orphan*/  dpm_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 TYPE_3__ dpm_prepared_list ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* to_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_device_pm_callback_end (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_device_pm_callback_start (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dpm_complete(pm_message_t state)
{
	struct list_head list;

	trace_suspend_resume(TPS("dpm_complete"), state.event, true);
	might_sleep();

	INIT_LIST_HEAD(&list);
	mutex_lock(&dpm_list_mtx);
	while (!list_empty(&dpm_prepared_list)) {
		struct device *dev = to_device(dpm_prepared_list.prev);

		get_device(dev);
		dev->power.is_prepared = false;
		list_move(&dev->power.entry, &list);
		mutex_unlock(&dpm_list_mtx);

		trace_device_pm_callback_start(dev, "", state.event);
		device_complete(dev, state);
		trace_device_pm_callback_end(dev, 0);

		mutex_lock(&dpm_list_mtx);
		put_device(dev);
	}
	list_splice(&list, &dpm_list);
	mutex_unlock(&dpm_list_mtx);

	/* Allow device probing and trigger re-probing of deferred devices */
	device_unblock_probing();
	trace_suspend_resume(TPS("dpm_complete"), state.event, false);
}
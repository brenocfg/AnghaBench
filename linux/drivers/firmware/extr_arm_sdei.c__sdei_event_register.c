#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sdei_event {int reregister; scalar_t__ type; int reenable; int /*<<< orphan*/  registered; int /*<<< orphan*/  event_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEI_EVENT_REGISTER_RM_ANY ; 
 scalar_t__ SDEI_EVENT_TYPE_SHARED ; 
 int /*<<< orphan*/  _local_event_register ; 
 int /*<<< orphan*/  _local_event_unregister ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int sdei_api_event_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdei_do_cross_call (int /*<<< orphan*/ ,struct sdei_event*) ; 
 int /*<<< orphan*/  sdei_entry_point ; 
 int /*<<< orphan*/  sdei_events_lock ; 
 int /*<<< orphan*/  sdei_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _sdei_event_register(struct sdei_event *event)
{
	int err;

	lockdep_assert_held(&sdei_events_lock);

	spin_lock(&sdei_list_lock);
	event->reregister = true;
	spin_unlock(&sdei_list_lock);

	if (event->type == SDEI_EVENT_TYPE_SHARED)
		return sdei_api_event_register(event->event_num,
					       sdei_entry_point,
					       event->registered,
					       SDEI_EVENT_REGISTER_RM_ANY, 0);


	err = sdei_do_cross_call(_local_event_register, event);
	if (err) {
		spin_lock(&sdei_list_lock);
		event->reregister = false;
		event->reenable = false;
		spin_unlock(&sdei_list_lock);

		sdei_do_cross_call(_local_event_unregister, event);
	}

	return err;
}
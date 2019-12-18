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
typedef  int /*<<< orphan*/  uint16_t ;
struct evdev_dev {int ev_kdb_active; int /*<<< orphan*/  ev_flags; scalar_t__ ev_report_opened; int /*<<< orphan*/  ev_led_states; int /*<<< orphan*/  ev_kdb_led_states; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EVDEV_ENTER (struct evdev_dev*) ; 
 int /*<<< orphan*/  EVDEV_EXIT (struct evdev_dev*) ; 
 int /*<<< orphan*/  EVDEV_FLAG_MT_AUTOREL ; 
 int /*<<< orphan*/  EVDEV_FLAG_MT_STCOMPAT ; 
 int /*<<< orphan*/  EV_LED ; 
 int /*<<< orphan*/  EV_SYN ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  SYN_REPORT ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ evdev_check_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  evdev_modify_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  evdev_restore_after_kdb (struct evdev_dev*) ; 
 int /*<<< orphan*/  evdev_send_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  evdev_send_mt_autorel (struct evdev_dev*) ; 
 int /*<<< orphan*/  evdev_send_mt_compat (struct evdev_dev*) ; 
 scalar_t__ kdb_active ; 

int
evdev_push_event(struct evdev_dev *evdev, uint16_t type, uint16_t code,
    int32_t value)
{

	if (evdev_check_event(evdev, type, code, value) != 0)
		return (EINVAL);

	/*
	 * Discard all but LEDs kdb events as unrelated to userspace.
	 * Aggregate LED updates and postpone reporting until kdb deactivation.
	 */
	if (kdb_active || SCHEDULER_STOPPED()) {
		evdev->ev_kdb_active = true;
		if (type == EV_LED)
			bit_set(evdev->ev_kdb_led_states,
			    bit_test(evdev->ev_led_states, code) != value);
		return (0);
	}

	EVDEV_ENTER(evdev);

	/* Fix evdev state corrupted with discarding of kdb events */
	if (evdev->ev_kdb_active) {
		evdev->ev_kdb_active = false;
		evdev_restore_after_kdb(evdev);
	}

	evdev_modify_event(evdev, type, code, &value);
	if (type == EV_SYN && code == SYN_REPORT &&
	     bit_test(evdev->ev_flags, EVDEV_FLAG_MT_AUTOREL))
		evdev_send_mt_autorel(evdev);
	if (type == EV_SYN && code == SYN_REPORT && evdev->ev_report_opened &&
	    bit_test(evdev->ev_flags, EVDEV_FLAG_MT_STCOMPAT))
		evdev_send_mt_compat(evdev);
	evdev_send_event(evdev, type, code, value);

	EVDEV_EXIT(evdev);

	return (0);
}
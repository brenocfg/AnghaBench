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
struct evdev_dev {int /*<<< orphan*/  ev_prop_flags; int /*<<< orphan*/  ev_abs_flags; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ evdev_count_fingers (struct evdev_dev*) ; 
 int evdev_get_mt_value (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** evdev_mtstmap ; 
 int /*<<< orphan*/  evdev_send_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_send_nfingers (struct evdev_dev*,scalar_t__) ; 
 scalar_t__ nitems (int /*<<< orphan*/ **) ; 

void
evdev_send_mt_compat(struct evdev_dev *evdev)
{
	int32_t nfingers, i;

	EVDEV_LOCK_ASSERT(evdev);

	nfingers = evdev_count_fingers(evdev);
	evdev_send_event(evdev, EV_KEY, BTN_TOUCH, nfingers > 0);

	if (evdev_get_mt_value(evdev, 0, ABS_MT_TRACKING_ID) != -1)
		/* Echo 0-th MT-slot as ST-slot */
		for (i = 0; i < nitems(evdev_mtstmap); i++)
			if (bit_test(evdev->ev_abs_flags, evdev_mtstmap[i][1]))
				evdev_send_event(evdev, EV_ABS,
				    evdev_mtstmap[i][1],
				    evdev_get_mt_value(evdev, 0,
				    evdev_mtstmap[i][0]));

	/* Touchscreens should not report tool taps */
	if (!bit_test(evdev->ev_prop_flags, INPUT_PROP_DIRECT))
		evdev_send_nfingers(evdev, nfingers);

	if (nfingers == 0)
		evdev_send_event(evdev, EV_ABS, ABS_PRESSURE, 0);
}
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
typedef  int uint16_t ;
struct evdev_dev {int /*<<< orphan*/  ev_clients; int /*<<< orphan*/  ev_key_states; int /*<<< orphan*/  ev_flags; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EVDEV_FLAG_SOFTREPEAT ; 
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
#define  EV_ABS 129 
#define  EV_KEY 128 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  KEY_EVENT_DOWN ; 
 int /*<<< orphan*/  KEY_EVENT_REPEAT ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int bit_test (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_event_supported (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_start_repeat (struct evdev_dev*,int) ; 
 int /*<<< orphan*/  evdev_stop_repeat (struct evdev_dev*) ; 

__attribute__((used)) static void
evdev_modify_event(struct evdev_dev *evdev, uint16_t type, uint16_t code,
    int32_t *value)
{

	EVDEV_LOCK_ASSERT(evdev);

	switch (type) {
	case EV_KEY:
		if (!evdev_event_supported(evdev, EV_REP))
			break;

		if (!bit_test(evdev->ev_flags, EVDEV_FLAG_SOFTREPEAT)) {
			/* Detect driver key repeats. */
			if (bit_test(evdev->ev_key_states, code) &&
			    *value == KEY_EVENT_DOWN)
				*value = KEY_EVENT_REPEAT;
		} else {
			/* Start/stop callout for evdev repeats */
			if (bit_test(evdev->ev_key_states, code) == !*value &&
			    !LIST_EMPTY(&evdev->ev_clients)) {
				if (*value == KEY_EVENT_DOWN)
					evdev_start_repeat(evdev, code);
				else
					evdev_stop_repeat(evdev);
			}
		}
		break;

	case EV_ABS:
		/* TBD: implement fuzz */
		break;
	}
}
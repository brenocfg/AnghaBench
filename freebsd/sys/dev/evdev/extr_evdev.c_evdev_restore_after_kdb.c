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
struct evdev_dev {int /*<<< orphan*/  ev_key_states; int /*<<< orphan*/  ev_kdb_led_states; int /*<<< orphan*/  ev_led_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_LED ; 
 int /*<<< orphan*/  EV_SYN ; 
 int KEY_CNT ; 
 int KEY_EVENT_UP ; 
 int LED_CNT ; 
 int /*<<< orphan*/  LED_MAX ; 
 int SYN_REPORT ; 
 int /*<<< orphan*/  bit_nclear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_send_event (struct evdev_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  evdev_stop_repeat (struct evdev_dev*) ; 

void
evdev_restore_after_kdb(struct evdev_dev *evdev)
{
	int code;

	EVDEV_LOCK_ASSERT(evdev);

	/* Report postponed leds */
	for (code = 0; code < LED_CNT; code++)
		if (bit_test(evdev->ev_kdb_led_states, code))
			evdev_send_event(evdev, EV_LED, code,
			    !bit_test(evdev->ev_led_states, code));
	bit_nclear(evdev->ev_kdb_led_states, 0, LED_MAX);

	/* Release stuck keys (CTRL + ALT + ESC) */
	evdev_stop_repeat(evdev);
	for (code = 0; code < KEY_CNT; code++) {
		if (bit_test(evdev->ev_key_states, code)) {
			evdev_send_event(evdev, EV_KEY, code, KEY_EVENT_UP);
			evdev_send_event(evdev, EV_SYN, SYN_REPORT, 1);
		}
	}
}
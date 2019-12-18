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
struct evdev_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * evdev_led_codes ; 
 int /*<<< orphan*/  evdev_push_led (struct evdev_dev*,int /*<<< orphan*/ ,int) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 

void
evdev_push_leds(struct evdev_dev *evdev, int leds)
{
	size_t i;

	/* Some drivers initialize leds before evdev */
	if (evdev == NULL)
		return;

	for (i = 0; i < nitems(evdev_led_codes); i++)
		evdev_push_led(evdev, evdev_led_codes[i], leds & (1 << i));
}
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
 int /*<<< orphan*/ * evdev_mouse_button_codes ; 
 int /*<<< orphan*/  evdev_push_key (struct evdev_dev*,int /*<<< orphan*/ ,int) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 

void
evdev_push_mouse_btn(struct evdev_dev *evdev, int buttons)
{
	size_t i;

	for (i = 0; i < nitems(evdev_mouse_button_codes); i++)
		evdev_push_key(evdev, evdev_mouse_button_codes[i],
		    buttons & (1 << i));
}
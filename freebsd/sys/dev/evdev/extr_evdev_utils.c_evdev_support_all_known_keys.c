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
 size_t KEY_RESERVED ; 
 scalar_t__ NONE ; 
 scalar_t__* evdev_at_set1_scancodes ; 
 int /*<<< orphan*/  evdev_support_key (struct evdev_dev*,scalar_t__) ; 
 size_t nitems (scalar_t__*) ; 

void
evdev_support_all_known_keys(struct evdev_dev *evdev)
{
	size_t i;

	for (i = KEY_RESERVED; i < nitems(evdev_at_set1_scancodes); i++)
		if (evdev_at_set1_scancodes[i] != NONE)
			evdev_support_key(evdev, evdev_at_set1_scancodes[i]);
}
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
struct evdev_dev {scalar_t__ ev_rep_key; int /*<<< orphan*/  ev_rep_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 scalar_t__ KEY_RESERVED ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
evdev_stop_repeat(struct evdev_dev *evdev)
{

	EVDEV_LOCK_ASSERT(evdev);

	if (evdev->ev_rep_key != KEY_RESERVED) {
		callout_stop(&evdev->ev_rep_callout);
		evdev->ev_rep_key = KEY_RESERVED;
	}
}
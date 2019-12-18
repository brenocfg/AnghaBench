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
struct evdev_dev {int* ev_rep; int /*<<< orphan*/  ev_rep_callout; int /*<<< orphan*/  ev_rep_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 size_t REP_DELAY ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct evdev_dev*) ; 
 int /*<<< orphan*/  evdev_repeat_callout ; 
 int hz ; 

__attribute__((used)) static void
evdev_start_repeat(struct evdev_dev *evdev, uint16_t key)
{

	EVDEV_LOCK_ASSERT(evdev);

	if (evdev->ev_rep[REP_DELAY]) {
		evdev->ev_rep_key = key;
		callout_reset(&evdev->ev_rep_callout,
		    evdev->ev_rep[REP_DELAY] * hz / 1000,
		    evdev_repeat_callout, evdev);
	}
}
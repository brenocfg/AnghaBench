#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct evdev_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kb_delay2; int /*<<< orphan*/  kb_delay1; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  REP_DELAY ; 
 int /*<<< orphan*/  REP_PERIOD ; 
 int /*<<< orphan*/  evdev_push_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
evdev_push_repeats(struct evdev_dev *evdev, keyboard_t *kbd)
{
	/* Some drivers initialize typematics before evdev */
	if (evdev == NULL)
		return;

	evdev_push_event(evdev, EV_REP, REP_DELAY, kbd->kb_delay1);
	evdev_push_event(evdev, EV_REP, REP_PERIOD, kbd->kb_delay2);
}
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
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/ * evdev_fngmap ; 
 int /*<<< orphan*/  evdev_send_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
evdev_send_nfingers(struct evdev_dev *evdev, int32_t nfingers)
{
	int32_t i;

	EVDEV_LOCK_ASSERT(evdev);

	if (nfingers > nitems(evdev_fngmap))
		nfingers = nitems(evdev_fngmap);

	for (i = 0; i < nitems(evdev_fngmap); i++)
		evdev_send_event(evdev, EV_KEY, evdev_fngmap[i],
		    nfingers == i + 1);
}
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
 int /*<<< orphan*/  EVDEV_ENTER (struct evdev_dev*) ; 
 int /*<<< orphan*/  EVDEV_EXIT (struct evdev_dev*) ; 
 int /*<<< orphan*/  evdev_send_mt_compat (struct evdev_dev*) ; 

void
evdev_push_mt_compat(struct evdev_dev *evdev)
{

	EVDEV_ENTER(evdev);
	evdev_send_mt_compat(evdev);
	EVDEV_EXIT(evdev);
}
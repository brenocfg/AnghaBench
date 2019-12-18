#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evdev_dev {TYPE_1__* ev_cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EVDEV ; 
 int /*<<< orphan*/  evdev_unregister (struct evdev_dev*) ; 
 int /*<<< orphan*/  free (struct evdev_dev*,int /*<<< orphan*/ ) ; 

void
evdev_free(struct evdev_dev *evdev)
{

	if (evdev != NULL && evdev->ev_cdev != NULL &&
	    evdev->ev_cdev->si_drv1 != NULL)
		evdev_unregister(evdev);

	free(evdev, M_EVDEV);
}
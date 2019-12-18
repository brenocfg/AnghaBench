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
typedef  scalar_t__ uint8_t ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int DEVICE_RESUME (int /*<<< orphan*/ *) ; 
 int DEVICE_SUSPEND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
usb_suspend_resume_sub(struct usb_device *udev, device_t dev, uint8_t do_suspend)
{
	int err;

	if (dev == NULL) {
		return;
	}
	if (!device_is_attached(dev)) {
		return;
	}
	if (do_suspend) {
		err = DEVICE_SUSPEND(dev);
	} else {
		err = DEVICE_RESUME(dev);
	}
	if (err) {
		device_printf(dev, "%s failed\n",
		    do_suspend ? "Suspend" : "Resume");
	}
}
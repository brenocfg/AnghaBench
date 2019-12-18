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
struct usb_device {int /*<<< orphan*/  ctrl_sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_enum_is_locked (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_sr_lock (struct usb_device*) ; 

void
usbd_ctrl_unlock(struct usb_device *udev)
{
	sx_xunlock(&udev->ctrl_sx);

	/*
	 * Restore the suspend and resume lock after we have unlocked
	 * the USB control transfer lock to avoid LOR:
	 */
	if (usbd_enum_is_locked(udev))
		usbd_sr_lock(udev);
}
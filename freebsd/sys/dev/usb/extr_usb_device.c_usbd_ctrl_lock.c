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
typedef  int uint8_t ;
struct usb_device {int /*<<< orphan*/  ctrl_sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sx_xlocked (int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_enum_is_locked (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_sr_unlock (struct usb_device*) ; 

uint8_t
usbd_ctrl_lock(struct usb_device *udev)
{
	if (sx_xlocked(&udev->ctrl_sx))
		return (0);
	sx_xlock(&udev->ctrl_sx);

	/*
	 * We need to allow suspend and resume at this point, else the
	 * control transfer will timeout if the device is suspended!
	 */
	if (usbd_enum_is_locked(udev))
		usbd_sr_unlock(udev);
	return (1);
}
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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_device {scalar_t__ ifaces_max; int /*<<< orphan*/ * cdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USB_ERR_NOT_CONFIGURED ; 

usb_error_t
usbd_interface_count(struct usb_device *udev, uint8_t *count)
{
	if (udev->cdesc == NULL) {
		*count = 0;
		return (USB_ERR_NOT_CONFIGURED);
	}
	*count = udev->ifaces_max;
	return (USB_ERR_NORMAL_COMPLETION);
}
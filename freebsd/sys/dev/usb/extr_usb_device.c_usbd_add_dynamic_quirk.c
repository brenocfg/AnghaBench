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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_device {scalar_t__* autoQuirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_NOMEM ; 
 size_t USB_MAX_AUTO_QUIRK ; 

usb_error_t
usbd_add_dynamic_quirk(struct usb_device *udev, uint16_t quirk)
{
	uint8_t x;

	for (x = 0; x != USB_MAX_AUTO_QUIRK; x++) {
		if (udev->autoQuirk[x] == 0 ||
		    udev->autoQuirk[x] == quirk) {
			udev->autoQuirk[x] = quirk;
			return (0);	/* success */
		}
	}
	return (USB_ERR_NOMEM);
}
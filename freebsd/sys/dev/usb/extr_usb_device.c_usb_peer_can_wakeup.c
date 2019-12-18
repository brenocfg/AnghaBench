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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {TYPE_1__ flags; struct usb_config_descriptor* cdesc; } ;
struct usb_config_descriptor {int bmAttributes; } ;

/* Variables and functions */
 int UC_REMOTE_WAKEUP ; 
 scalar_t__ USB_MODE_HOST ; 

uint8_t
usb_peer_can_wakeup(struct usb_device *udev)
{
	const struct usb_config_descriptor *cdp;

	cdp = udev->cdesc;
	if ((cdp != NULL) && (udev->flags.usb_mode == USB_MODE_HOST)) {
		return (cdp->bmAttributes & UC_REMOTE_WAKEUP);
	}
	return (0);			/* not supported */
}
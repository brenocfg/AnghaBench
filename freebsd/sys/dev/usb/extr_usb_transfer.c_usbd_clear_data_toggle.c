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
struct usb_endpoint {scalar_t__ toggle_next; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_device*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_clear_stall_locked (struct usb_device*,struct usb_endpoint*) ; 

void
usbd_clear_data_toggle(struct usb_device *udev, struct usb_endpoint *ep)
{
	DPRINTFN(5, "udev=%p endpoint=%p\n", udev, ep);

	USB_BUS_LOCK(udev->bus);
	ep->toggle_next = 0;
	/* some hardware needs a callback to clear the data toggle */
	usbd_clear_stall_locked(udev, ep);
	USB_BUS_UNLOCK(udev->bus);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_endpoint {int /*<<< orphan*/ * methods; } ;
struct TYPE_4__ {scalar_t__ usb_mode; } ;
struct usb_device {TYPE_3__* bus; int /*<<< orphan*/ * parent_hub; TYPE_1__ flags; } ;
struct TYPE_6__ {TYPE_2__* methods; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* clear_stall ) (struct usb_device*,struct usb_endpoint*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_MODE_HOST ; 
 int /*<<< orphan*/  stub1 (struct usb_device*,struct usb_endpoint*) ; 

void
usbd_clear_stall_locked(struct usb_device *udev, struct usb_endpoint *ep)
{
	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	/* check that we have a valid case */
	if (udev->flags.usb_mode == USB_MODE_HOST &&
	    udev->parent_hub != NULL &&
	    udev->bus->methods->clear_stall != NULL &&
	    ep->methods != NULL) {
		(udev->bus->methods->clear_stall) (udev, ep);
	}
}
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
struct TYPE_4__ {scalar_t__ isochronous_xfr; } ;
struct usb_xfer {TYPE_3__* xroot; TYPE_1__ flags_int; } ;
struct TYPE_6__ {TYPE_2__* udev; } ;
struct TYPE_5__ {int speed; } ;

/* Variables and functions */
#define  USB_SPEED_FULL 128 
 int /*<<< orphan*/  usb_hs_bandwidth_alloc (struct usb_xfer*) ; 

__attribute__((used)) static void
xhci_device_generic_open(struct usb_xfer *xfer)
{
	if (xfer->flags_int.isochronous_xfr) {
		switch (xfer->xroot->udev->speed) {
		case USB_SPEED_FULL:
			break;
		default:
			usb_hs_bandwidth_alloc(xfer);
			break;
		}
	}
}
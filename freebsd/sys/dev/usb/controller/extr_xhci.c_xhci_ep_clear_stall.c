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
struct xhci_endpoint_ext {int trb_halted; scalar_t__ trb_running; } ;
struct usb_endpoint {int /*<<< orphan*/  edesc; } ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {int /*<<< orphan*/  bus; int /*<<< orphan*/ * parent_hub; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_MODE_HOST ; 
 struct xhci_endpoint_ext* xhci_get_endpoint_ext (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xhci_ep_clear_stall(struct usb_device *udev, struct usb_endpoint *ep)
{
	struct xhci_endpoint_ext *pepext;

	DPRINTF("\n");

	if (udev->flags.usb_mode != USB_MODE_HOST) {
		/* not supported */
		return;
	}
	if (udev->parent_hub == NULL) {
		/* root HUB has special endpoint handling */
		return;
	}

	pepext = xhci_get_endpoint_ext(udev, ep->edesc);

	USB_BUS_LOCK(udev->bus);
	pepext->trb_halted = 1;
	pepext->trb_running = 0;
	USB_BUS_UNLOCK(udev->bus);
}
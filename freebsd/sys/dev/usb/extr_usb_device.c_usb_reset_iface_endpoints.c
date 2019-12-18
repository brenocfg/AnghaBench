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
struct usb_endpoint {scalar_t__ iface_index; int /*<<< orphan*/ * edesc; } ;
struct usb_device {int endpoints_max; struct usb_endpoint* endpoints; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbd_set_endpoint_stall (struct usb_device*,struct usb_endpoint*,int /*<<< orphan*/ ) ; 

usb_error_t
usb_reset_iface_endpoints(struct usb_device *udev, uint8_t iface_index)
{
	struct usb_endpoint *ep;
	struct usb_endpoint *ep_end;

	ep = udev->endpoints;
	ep_end = udev->endpoints + udev->endpoints_max;

	for (; ep != ep_end; ep++) {

		if ((ep->edesc == NULL) ||
		    (ep->iface_index != iface_index)) {
			continue;
		}
		/* simulate a clear stall from the peer */
		usbd_set_endpoint_stall(udev, ep, 0);
	}
	return (0);
}
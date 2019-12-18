#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t usb_stream_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_endpoint_ss_comp_descriptor {int /*<<< orphan*/  bmAttributes; } ;
struct usb_endpoint_descriptor {int bmAttributes; } ;
struct usb_endpoint {int /*<<< orphan*/ * methods; TYPE_1__* endpoint_q; int /*<<< orphan*/  iface_index; struct usb_endpoint_ss_comp_descriptor* ecomp; struct usb_endpoint_descriptor* edesc; } ;
struct usb_device {scalar_t__ speed; TYPE_2__* bus; } ;
struct usb_bus_methods {int /*<<< orphan*/  (* clear_stall ) (struct usb_device*,struct usb_endpoint*) ;int /*<<< orphan*/  (* endpoint_init ) (struct usb_device*,struct usb_endpoint_descriptor*,struct usb_endpoint*) ;} ;
struct TYPE_5__ {struct usb_bus_methods* methods; } ;
struct TYPE_4__ {int /*<<< orphan*/ * command; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int UE_BULK ; 
 scalar_t__ UE_GET_BULK_STREAMS (int /*<<< orphan*/ ) ; 
 int UE_XFERTYPE ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  USB_EP_MODE_DEFAULT ; 
 int /*<<< orphan*/  USB_EP_MODE_STREAMS ; 
 size_t USB_MAX_EP_STREAMS ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int /*<<< orphan*/  stub1 (struct usb_device*,struct usb_endpoint_descriptor*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  stub2 (struct usb_device*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  usbd_pipe_start ; 
 int /*<<< orphan*/  usbd_set_endpoint_mode (struct usb_device*,struct usb_endpoint*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_init_endpoint(struct usb_device *udev, uint8_t iface_index,
    struct usb_endpoint_descriptor *edesc,
    struct usb_endpoint_ss_comp_descriptor *ecomp,
    struct usb_endpoint *ep)
{
	const struct usb_bus_methods *methods;
	usb_stream_t x;

	methods = udev->bus->methods;

	(methods->endpoint_init) (udev, edesc, ep);

	/* initialise USB endpoint structure */
	ep->edesc = edesc;
	ep->ecomp = ecomp;
	ep->iface_index = iface_index;

	/* setup USB stream queues */
	for (x = 0; x != USB_MAX_EP_STREAMS; x++) {
		TAILQ_INIT(&ep->endpoint_q[x].head);
		ep->endpoint_q[x].command = &usbd_pipe_start;
	}

	/* the pipe is not supported by the hardware */
 	if (ep->methods == NULL)
		return;

	/* check for SUPER-speed streams mode endpoint */
	if (udev->speed == USB_SPEED_SUPER && ecomp != NULL &&
	    (edesc->bmAttributes & UE_XFERTYPE) == UE_BULK &&
	    (UE_GET_BULK_STREAMS(ecomp->bmAttributes) != 0)) {
		usbd_set_endpoint_mode(udev, ep, USB_EP_MODE_STREAMS);
	} else {
		usbd_set_endpoint_mode(udev, ep, USB_EP_MODE_DEFAULT);
	}

	/* clear stall, if any */
	if (methods->clear_stall != NULL) {
		USB_BUS_LOCK(udev->bus);
		(methods->clear_stall) (udev, ep);
		USB_BUS_UNLOCK(udev->bus);
	}
}
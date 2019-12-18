#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint16_t ;
struct usb_hw_ep_scratch_sub {scalar_t__ needs_out; scalar_t__ needs_in; } ;
struct usb_hw_ep_scratch {struct usb_hw_ep_scratch_sub* ep; struct usb_hw_ep_scratch_sub* ep_max; struct usb_device* udev; struct usb_bus_methods const* methods; void* cd; } ;
struct usb_hw_ep_profile {int max_in_frame_size; } ;
struct usb_device_descriptor {int bMaxPacketSize; } ;
struct TYPE_4__ {struct usb_hw_ep_scratch* hw_ep_scratch; } ;
struct usb_device {scalar_t__ speed; TYPE_2__ scratch; TYPE_1__* bus; } ;
struct usb_descriptor {scalar_t__ bDescriptorType; int bLength; } ;
struct usb_bus_methods {int /*<<< orphan*/  (* get_hw_ep_profile ) (struct usb_device*,struct usb_hw_ep_profile const**,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct usb_bus_methods* methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UDESC_CONFIG ; 
 scalar_t__ UDESC_DEVICE ; 
 int /*<<< orphan*/  UE_BULK ; 
 int /*<<< orphan*/  UE_CONTROL ; 
 int /*<<< orphan*/  UE_INTERRUPT ; 
 int /*<<< orphan*/  UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  memset (struct usb_hw_ep_scratch*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct usb_device*,struct usb_hw_ep_profile const**,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_hw_ep_find_match (struct usb_hw_ep_scratch*,struct usb_hw_ep_scratch_sub*,int) ; 
 scalar_t__ usb_hw_ep_get_needs (struct usb_hw_ep_scratch*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_hw_ep_match (struct usb_hw_ep_profile const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
usb_hw_ep_resolve(struct usb_device *udev,
    struct usb_descriptor *desc)
{
	struct usb_hw_ep_scratch *ues;
	struct usb_hw_ep_scratch_sub *ep;
	const struct usb_hw_ep_profile *pf;
	const struct usb_bus_methods *methods;
	struct usb_device_descriptor *dd;
	uint16_t mps;

	if (desc == NULL)
		return (USB_ERR_INVAL);

	/* get bus methods */
	methods = udev->bus->methods;

	if (methods->get_hw_ep_profile == NULL)
		return (USB_ERR_INVAL);

	if (desc->bDescriptorType == UDESC_DEVICE) {

		if (desc->bLength < sizeof(*dd))
			return (USB_ERR_INVAL);

		dd = (void *)desc;

		/* get HW control endpoint 0 profile */
		(methods->get_hw_ep_profile) (udev, &pf, 0);
		if (pf == NULL) {
			return (USB_ERR_INVAL);
		}
		if (!usb_hw_ep_match(pf, UE_CONTROL, 0)) {
			DPRINTFN(0, "Endpoint 0 does not "
			    "support control\n");
			return (USB_ERR_INVAL);
		}
		mps = dd->bMaxPacketSize;

		if (udev->speed == USB_SPEED_FULL) {
			/*
			 * We can optionally choose another packet size !
			 */
			while (1) {
				/* check if "mps" is ok */
				if (pf->max_in_frame_size >= mps) {
					break;
				}
				/* reduce maximum packet size */
				mps /= 2;

				/* check if "mps" is too small */
				if (mps < 8) {
					return (USB_ERR_INVAL);
				}
			}

			dd->bMaxPacketSize = mps;

		} else {
			/* We only have one choice */
			if (mps == 255) {
				mps = 512;
			}
			/* Check if we support the specified wMaxPacketSize */
			if (pf->max_in_frame_size < mps) {
				return (USB_ERR_INVAL);
			}
		}
		return (0);		/* success */
	}
	if (desc->bDescriptorType != UDESC_CONFIG)
		return (USB_ERR_INVAL);
	if (desc->bLength < sizeof(*(ues->cd)))
		return (USB_ERR_INVAL);

	ues = udev->scratch.hw_ep_scratch;

	memset(ues, 0, sizeof(*ues));

	ues->ep_max = ues->ep;
	ues->cd = (void *)desc;
	ues->methods = methods;
	ues->udev = udev;

	/* Get all the endpoints we need */

	if (usb_hw_ep_get_needs(ues, UE_ISOCHRONOUS, 0) ||
	    usb_hw_ep_get_needs(ues, UE_INTERRUPT, 0) ||
	    usb_hw_ep_get_needs(ues, UE_CONTROL, 0) ||
	    usb_hw_ep_get_needs(ues, UE_BULK, 0)) {
		DPRINTFN(0, "Could not get needs\n");
		return (USB_ERR_INVAL);
	}
	for (ep = ues->ep; ep != ues->ep_max; ep++) {

		while (ep->needs_in || ep->needs_out) {

			/*
		         * First try to use a simplex endpoint.
		         * Then try to use a duplex endpoint.
		         */
			if (usb_hw_ep_find_match(ues, ep, 1) &&
			    usb_hw_ep_find_match(ues, ep, 0)) {
				DPRINTFN(0, "Could not find match\n");
				return (USB_ERR_INVAL);
			}
		}
	}

	ues->ep_max = ues->ep;

	/* Update all endpoint addresses */

	if (usb_hw_ep_get_needs(ues, UE_ISOCHRONOUS, 1) ||
	    usb_hw_ep_get_needs(ues, UE_INTERRUPT, 1) ||
	    usb_hw_ep_get_needs(ues, UE_CONTROL, 1) ||
	    usb_hw_ep_get_needs(ues, UE_BULK, 1)) {
		DPRINTFN(0, "Could not update endpoint address\n");
		return (USB_ERR_INVAL);
	}
	return (0);			/* success */
}
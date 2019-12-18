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
typedef  int uint16_t ;
struct usb_endpoint_descriptor {int bmAttributes; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_endpoint {int /*<<< orphan*/ * methods; } ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {scalar_t__ speed; TYPE_1__ flags; int /*<<< orphan*/ * parent_hub; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int SOTG_HS_MAX_PACKET_SIZE ; 
#define  UE_ISOCHRONOUS 128 
 int UE_XFERTYPE ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  saf1761_otg_device_isoc_methods ; 
 int /*<<< orphan*/  saf1761_otg_host_isoc_methods ; 
 int /*<<< orphan*/  saf1761_otg_non_isoc_methods ; 

__attribute__((used)) static void
saf1761_otg_ep_init(struct usb_device *udev, struct usb_endpoint_descriptor *edesc,
    struct usb_endpoint *ep)
{
	uint16_t mps;

	DPRINTFN(2, "endpoint=%p, addr=%d, endpt=%d, mode=%d\n",
	    ep, udev->address,
	    edesc->bEndpointAddress, udev->flags.usb_mode);

	if (udev->parent_hub == NULL) {
		/* root HUB has special endpoint handling */
		return;
	}

	/* Verify wMaxPacketSize */
	mps = UGETW(edesc->wMaxPacketSize);
	if (udev->speed == USB_SPEED_HIGH) {
		if ((mps >> 11) & 3) {
			DPRINTF("A packet multiplier different from "
			    "1 is not supported\n");
			return;
		}
	}
	if (mps > SOTG_HS_MAX_PACKET_SIZE) {
		DPRINTF("Packet size %d bigger than %d\n",
		    (int)mps, SOTG_HS_MAX_PACKET_SIZE);
		return;
	}
	if (udev->flags.usb_mode == USB_MODE_DEVICE) {
		if (udev->speed != USB_SPEED_FULL &&
		    udev->speed != USB_SPEED_HIGH) {
			/* not supported */
			return;
		}
		switch (edesc->bmAttributes & UE_XFERTYPE) {
		case UE_ISOCHRONOUS:
			ep->methods = &saf1761_otg_device_isoc_methods;
			break;
		default:
			ep->methods = &saf1761_otg_non_isoc_methods;
			break;
		}
	} else {
		switch (edesc->bmAttributes & UE_XFERTYPE) {
		case UE_ISOCHRONOUS:
			ep->methods = &saf1761_otg_host_isoc_methods;
			break;
		default:
			ep->methods = &saf1761_otg_non_isoc_methods;
			break;
		}
	}
}
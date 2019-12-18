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
struct usb_endpoint_descriptor {int* wMaxPacketSize; int bmAttributes; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_endpoint {int /*<<< orphan*/ * methods; } ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {scalar_t__ device_index; scalar_t__ speed; TYPE_1__ flags; int /*<<< orphan*/  address; int /*<<< orphan*/  bus; } ;
struct dwc_otg_softc {scalar_t__ sc_rt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 struct dwc_otg_softc* DWC_OTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int UE_ISOCHRONOUS ; 
 int UE_XFERTYPE ; 
 scalar_t__ USB_MODE_DEVICE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dwc_otg_device_isoc_methods ; 
 int /*<<< orphan*/  dwc_otg_device_non_isoc_methods ; 

__attribute__((used)) static void
dwc_otg_ep_init(struct usb_device *udev, struct usb_endpoint_descriptor *edesc,
    struct usb_endpoint *ep)
{
	struct dwc_otg_softc *sc = DWC_OTG_BUS2SC(udev->bus);

	DPRINTFN(2, "endpoint=%p, addr=%d, endpt=%d, mode=%d (%d,%d)\n",
	    ep, udev->address,
	    edesc->bEndpointAddress, udev->flags.usb_mode,
	    sc->sc_rt_addr, udev->device_index);

	if (udev->device_index != sc->sc_rt_addr) {

		if (udev->flags.usb_mode == USB_MODE_DEVICE) {
			if (udev->speed != USB_SPEED_FULL &&
			    udev->speed != USB_SPEED_HIGH) {
				/* not supported */
				return;
			}
		} else {
			if (udev->speed == USB_SPEED_HIGH &&
			    (edesc->wMaxPacketSize[1] & 0x18) != 0 &&
			    (edesc->bmAttributes & UE_XFERTYPE) != UE_ISOCHRONOUS) {
				/* not supported */
				DPRINTFN(-1, "Non-isochronous high bandwidth "
				    "endpoint not supported\n");
				return;
			}
		}
		if ((edesc->bmAttributes & UE_XFERTYPE) == UE_ISOCHRONOUS)
			ep->methods = &dwc_otg_device_isoc_methods;
		else
			ep->methods = &dwc_otg_device_non_isoc_methods;
	}
}
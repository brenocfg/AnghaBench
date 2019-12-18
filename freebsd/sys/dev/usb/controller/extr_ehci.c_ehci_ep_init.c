#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_endpoint_descriptor {int bmAttributes; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_endpoint {int /*<<< orphan*/ * methods; } ;
struct TYPE_5__ {int /*<<< orphan*/  usb_mode; } ;
struct usb_device {scalar_t__ device_index; scalar_t__ speed; scalar_t__ hs_hub_addr; scalar_t__ hs_port_no; TYPE_2__* parent_hs_hub; TYPE_1__ flags; int /*<<< orphan*/  address; int /*<<< orphan*/  bus; } ;
struct TYPE_7__ {scalar_t__ sc_addr; } ;
typedef  TYPE_3__ ehci_softc_t ;
struct TYPE_6__ {int /*<<< orphan*/ * hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* EHCI_BUS2SC (int /*<<< orphan*/ ) ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int UE_XFERTYPE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  ehci_device_bulk_methods ; 
 int /*<<< orphan*/  ehci_device_ctrl_methods ; 
 int /*<<< orphan*/  ehci_device_intr_methods ; 
 int /*<<< orphan*/  ehci_device_isoc_fs_methods ; 
 int /*<<< orphan*/  ehci_device_isoc_hs_methods ; 

__attribute__((used)) static void
ehci_ep_init(struct usb_device *udev, struct usb_endpoint_descriptor *edesc,
    struct usb_endpoint *ep)
{
	ehci_softc_t *sc = EHCI_BUS2SC(udev->bus);

	DPRINTFN(2, "endpoint=%p, addr=%d, endpt=%d, mode=%d (%d)\n",
	    ep, udev->address,
	    edesc->bEndpointAddress, udev->flags.usb_mode,
	    sc->sc_addr);

	if (udev->device_index != sc->sc_addr) {

		if ((udev->speed != USB_SPEED_HIGH) &&
		    ((udev->hs_hub_addr == 0) ||
		    (udev->hs_port_no == 0) ||
		    (udev->parent_hs_hub == NULL) ||
		    (udev->parent_hs_hub->hub == NULL))) {
			/* We need a transaction translator */
			goto done;
		}
		switch (edesc->bmAttributes & UE_XFERTYPE) {
		case UE_CONTROL:
			ep->methods = &ehci_device_ctrl_methods;
			break;
		case UE_INTERRUPT:
			ep->methods = &ehci_device_intr_methods;
			break;
		case UE_ISOCHRONOUS:
			if (udev->speed == USB_SPEED_HIGH) {
				ep->methods = &ehci_device_isoc_hs_methods;
			} else if (udev->speed == USB_SPEED_FULL) {
				ep->methods = &ehci_device_isoc_fs_methods;
			}
			break;
		case UE_BULK:
			ep->methods = &ehci_device_bulk_methods;
			break;
		default:
			/* do nothing */
			break;
		}
	}
done:
	return;
}
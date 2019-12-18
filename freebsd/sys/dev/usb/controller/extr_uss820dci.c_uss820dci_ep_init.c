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
struct uss820dci_softc {scalar_t__ sc_rt_addr; } ;
struct usb_endpoint_descriptor {int bmAttributes; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_endpoint {int /*<<< orphan*/ * methods; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_mode; } ;
struct usb_device {scalar_t__ device_index; scalar_t__ speed; TYPE_1__ flags; int /*<<< orphan*/  address; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int UE_XFERTYPE ; 
 scalar_t__ USB_SPEED_FULL ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uss820dci_device_bulk_methods ; 
 int /*<<< orphan*/  uss820dci_device_ctrl_methods ; 
 int /*<<< orphan*/  uss820dci_device_intr_methods ; 
 int /*<<< orphan*/  uss820dci_device_isoc_fs_methods ; 

__attribute__((used)) static void
uss820dci_ep_init(struct usb_device *udev, struct usb_endpoint_descriptor *edesc,
    struct usb_endpoint *ep)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(udev->bus);

	DPRINTFN(2, "endpoint=%p, addr=%d, endpt=%d, mode=%d (%d)\n",
	    ep, udev->address,
	    edesc->bEndpointAddress, udev->flags.usb_mode,
	    sc->sc_rt_addr);

	if (udev->device_index != sc->sc_rt_addr) {

		if (udev->speed != USB_SPEED_FULL) {
			/* not supported */
			return;
		}
		switch (edesc->bmAttributes & UE_XFERTYPE) {
		case UE_CONTROL:
			ep->methods = &uss820dci_device_ctrl_methods;
			break;
		case UE_INTERRUPT:
			ep->methods = &uss820dci_device_intr_methods;
			break;
		case UE_ISOCHRONOUS:
			ep->methods = &uss820dci_device_isoc_fs_methods;
			break;
		case UE_BULK:
			ep->methods = &uss820dci_device_bulk_methods;
			break;
		default:
			/* do nothing */
			break;
		}
	}
}
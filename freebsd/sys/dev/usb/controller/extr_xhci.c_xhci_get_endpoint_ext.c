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
typedef  size_t uint8_t ;
struct TYPE_4__ {TYPE_1__* devs; } ;
struct xhci_softc {TYPE_2__ sc_hw; } ;
struct xhci_endpoint_ext {int /*<<< orphan*/  physaddr; int /*<<< orphan*/  trb; struct usb_page_cache* page_cache; } ;
struct usb_page_search {int /*<<< orphan*/  physaddr; int /*<<< orphan*/  buffer; } ;
struct usb_page_cache {int dummy; } ;
struct usb_endpoint_descriptor {size_t bEndpointAddress; int bmAttributes; } ;
struct usb_device {size_t controller_slot_id; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {struct xhci_endpoint_ext* endp; struct usb_page_cache* endpoint_pc; } ;

/* Variables and functions */
 int UE_CONTROL ; 
 size_t UE_DIR_IN ; 
 int UE_XFERTYPE ; 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 size_t XHCI_EPNO2EPID (size_t) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 

__attribute__((used)) static struct xhci_endpoint_ext *
xhci_get_endpoint_ext(struct usb_device *udev, struct usb_endpoint_descriptor *edesc)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	struct xhci_endpoint_ext *pepext;
	struct usb_page_cache *pc;
	struct usb_page_search buf_ep;
	uint8_t epno;
	uint8_t index;

	epno = edesc->bEndpointAddress;
	if ((edesc->bmAttributes & UE_XFERTYPE) == UE_CONTROL)
		epno |= UE_DIR_IN;

	epno = XHCI_EPNO2EPID(epno);

	index = udev->controller_slot_id;

	pc = &sc->sc_hw.devs[index].endpoint_pc[epno];

	usbd_get_page(pc, 0, &buf_ep);

	pepext = &sc->sc_hw.devs[index].endp[epno];
	pepext->page_cache = pc;
	pepext->trb = buf_ep.buffer;
	pepext->physaddr = buf_ep.physaddr;

	return (pepext);
}
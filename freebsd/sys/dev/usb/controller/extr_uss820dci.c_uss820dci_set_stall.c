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
typedef  int uint8_t ;
struct uss820dci_softc {int /*<<< orphan*/  sc_bus; } ;
struct usb_endpoint {TYPE_1__* edesc; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int bEndpointAddress; int bmAttributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UE_ADDR ; 
 int UE_CONTROL ; 
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
 int UE_XFERTYPE ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USS820_EPCON ; 
 int USS820_EPCON_RXSTL ; 
 int USS820_EPCON_TXSTL ; 
 int /*<<< orphan*/  USS820_EPINDEX ; 
 int /*<<< orphan*/  USS820_WRITE_1 (struct uss820dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uss820dci_update_shared_1 (struct uss820dci_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
uss820dci_set_stall(struct usb_device *udev,
    struct usb_endpoint *ep, uint8_t *did_stall)
{
	struct uss820dci_softc *sc;
	uint8_t ep_no;
	uint8_t ep_type;
	uint8_t ep_dir;
	uint8_t temp;

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	DPRINTFN(5, "endpoint=%p\n", ep);

	/* set FORCESTALL */
	sc = USS820_DCI_BUS2SC(udev->bus);
	ep_no = (ep->edesc->bEndpointAddress & UE_ADDR);
	ep_dir = (ep->edesc->bEndpointAddress & (UE_DIR_IN | UE_DIR_OUT));
	ep_type = (ep->edesc->bmAttributes & UE_XFERTYPE);

	if (ep_type == UE_CONTROL) {
		/* should not happen */
		return;
	}
	USB_BUS_SPIN_LOCK(&sc->sc_bus);
	USS820_WRITE_1(sc, USS820_EPINDEX, ep_no);

	if (ep_dir == UE_DIR_IN) {
		temp = USS820_EPCON_TXSTL;
	} else {
		temp = USS820_EPCON_RXSTL;
	}
	uss820dci_update_shared_1(sc, USS820_EPCON, 0xFF, temp);
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
}
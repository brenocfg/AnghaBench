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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct usb_endpoint {TYPE_2__* edesc; } ;
struct TYPE_3__ {scalar_t__ usb_mode; } ;
struct usb_device {int /*<<< orphan*/  bus; TYPE_1__ flags; } ;
struct dwc_otg_softc {int* sc_in_ctl; int* sc_out_ctl; unsigned int sc_active_rx_ep; scalar_t__ sc_last_rx_status; int /*<<< orphan*/  sc_bus; } ;
struct TYPE_4__ {int bEndpointAddress; } ;

/* Variables and functions */
 int DOEPCTL_EPDIS ; 
 int DOEPCTL_STALL ; 
 int DOTG_DIEPCTL (int) ; 
 int DOTG_DOEPCTL (int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 struct dwc_otg_softc* DWC_OTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int,int) ; 
 int GRXSTSRD_CHNUM_GET (scalar_t__) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UE_ADDR ; 
 int UE_DIR_IN ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  dwc_otg_common_rx_ack (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_interrupt_complete_locked (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_interrupt_poll_locked (struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_set_stall(struct usb_device *udev,
    struct usb_endpoint *ep, uint8_t *did_stall)
{
	struct dwc_otg_softc *sc;
	uint32_t temp;
	uint32_t reg;
	uint8_t ep_no;

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	/* check mode */
	if (udev->flags.usb_mode != USB_MODE_DEVICE) {
		/* not supported */
		return;
	}

	sc = DWC_OTG_BUS2SC(udev->bus);

	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	/* get endpoint address */
	ep_no = ep->edesc->bEndpointAddress;

	DPRINTFN(5, "endpoint=0x%x\n", ep_no);

	if (ep_no & UE_DIR_IN) {
		reg = DOTG_DIEPCTL(ep_no & UE_ADDR);
		temp = sc->sc_in_ctl[ep_no & UE_ADDR];
	} else {
		reg = DOTG_DOEPCTL(ep_no & UE_ADDR);
		temp = sc->sc_out_ctl[ep_no & UE_ADDR];
	}

	/* disable and stall endpoint */
	DWC_OTG_WRITE_4(sc, reg, temp | DOEPCTL_EPDIS);
	DWC_OTG_WRITE_4(sc, reg, temp | DOEPCTL_STALL);

	/* clear active OUT ep */
	if (!(ep_no & UE_DIR_IN)) {

		sc->sc_active_rx_ep &= ~(1U << (ep_no & UE_ADDR));

		if (sc->sc_last_rx_status != 0 &&
		    (ep_no & UE_ADDR) == GRXSTSRD_CHNUM_GET(
		    sc->sc_last_rx_status)) {
			/* dump data */
			dwc_otg_common_rx_ack(sc);
			/* poll interrupt */
			dwc_otg_interrupt_poll_locked(sc);
			dwc_otg_interrupt_complete_locked(sc);
		}
	}
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
}
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
typedef  int uint32_t ;
struct TYPE_2__ {int status_device_mode; int status_bus_reset; int change_connect; int status_low_speed; int port_enabled; int status_high_speed; int change_enabled; int change_over_current; int port_over_current; int port_powered; scalar_t__ change_suspend; scalar_t__ status_suspend; } ;
struct dwc_otg_softc {int sc_irq_mask; int sc_hprt_val; scalar_t__ sc_xfer_complete; int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_DSTS ; 
 int /*<<< orphan*/  DOTG_GINTMSK ; 
 int /*<<< orphan*/  DOTG_GINTSTS ; 
 int /*<<< orphan*/  DOTG_GOTGCTL ; 
 int /*<<< orphan*/  DOTG_HAINT ; 
 int /*<<< orphan*/  DOTG_HFNUM ; 
 int /*<<< orphan*/  DOTG_HPRT ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 scalar_t__ DSTS_ENUMSPD_GET (int) ; 
 scalar_t__ DSTS_ENUMSPD_HI ; 
 int /*<<< orphan*/  DWC_MODE_DEVICE ; 
 int DWC_OTG_MSK_GINT_THREAD_IRQ ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int GINTMSK_OTGINTMSK ; 
 int GINTMSK_SOFMSK ; 
 int GINTMSK_USBSUSPMSK ; 
 int GINTMSK_WKUPINTMSK ; 
 int GINTSTS_ENUMDONE ; 
 int GINTSTS_PRTINT ; 
 int GINTSTS_SESSREQINT ; 
 int GINTSTS_USBRST ; 
 int GINTSTS_USBSUSP ; 
 int GINTSTS_WKUPINT ; 
 int GOTGCTL_ASESVLD ; 
 int GOTGCTL_BSESVLD ; 
 int HPRT_PRTCONNDET ; 
 int HPRT_PRTCONNSTS ; 
 int HPRT_PRTENA ; 
 int HPRT_PRTENCHNG ; 
 int HPRT_PRTOVRCURRACT ; 
 int HPRT_PRTOVRCURRCHNG ; 
 int HPRT_PRTPWR ; 
 int HPRT_PRTSPD_HIGH ; 
 int HPRT_PRTSPD_LOW ; 
 int HPRT_PRTSPD_MASK ; 
 int HPRT_PRTSPD_SHIFT ; 
 int HPRT_PRTSUSP ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_init_fifo (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_interrupt_complete_locked (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_resume_irq (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_root_intr (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_set_address (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_suspend_irq (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_update_host_frame_interval (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_vbus_interrupt (struct dwc_otg_softc*,int) ; 

void
dwc_otg_interrupt(void *arg)
{
	struct dwc_otg_softc *sc = arg;
	uint32_t status;

	USB_BUS_LOCK(&sc->sc_bus);
	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	/* read and clear interrupt status */
	status = DWC_OTG_READ_4(sc, DOTG_GINTSTS);

	/* clear interrupts we are handling here */
	DWC_OTG_WRITE_4(sc, DOTG_GINTSTS, status & DWC_OTG_MSK_GINT_THREAD_IRQ);

	DPRINTFN(14, "GINTSTS=0x%08x HAINT=0x%08x HFNUM=0x%08x\n",
	    status, DWC_OTG_READ_4(sc, DOTG_HAINT),
	    DWC_OTG_READ_4(sc, DOTG_HFNUM));

	if (status & GINTSTS_USBRST) {

		/* set correct state */
		sc->sc_flags.status_device_mode = 1;
		sc->sc_flags.status_bus_reset = 0;
		sc->sc_flags.status_suspend = 0;
		sc->sc_flags.change_suspend = 0;
		sc->sc_flags.change_connect = 1;

		/* Disable SOF interrupt */
		sc->sc_irq_mask &= ~GINTMSK_SOFMSK;
		DWC_OTG_WRITE_4(sc, DOTG_GINTMSK, sc->sc_irq_mask);

		/* complete root HUB interrupt endpoint */
		dwc_otg_root_intr(sc);
	}

	/* check for any bus state change interrupts */
	if (status & GINTSTS_ENUMDONE) {

		uint32_t temp;

		DPRINTFN(5, "end of reset\n");

		/* set correct state */
		sc->sc_flags.status_device_mode = 1;
		sc->sc_flags.status_bus_reset = 1;
		sc->sc_flags.status_suspend = 0;
		sc->sc_flags.change_suspend = 0;
		sc->sc_flags.change_connect = 1;
		sc->sc_flags.status_low_speed = 0;
		sc->sc_flags.port_enabled = 1;

		/* reset FIFOs */
		(void) dwc_otg_init_fifo(sc, DWC_MODE_DEVICE);

		/* reset function address */
		dwc_otg_set_address(sc, 0);

		/* figure out enumeration speed */
		temp = DWC_OTG_READ_4(sc, DOTG_DSTS);
		if (DSTS_ENUMSPD_GET(temp) == DSTS_ENUMSPD_HI)
			sc->sc_flags.status_high_speed = 1;
		else
			sc->sc_flags.status_high_speed = 0;

		/*
		 * Disable resume and SOF interrupt, and enable
		 * suspend and RX frame interrupt:
		 */
		sc->sc_irq_mask &= ~(GINTMSK_WKUPINTMSK | GINTMSK_SOFMSK);
		sc->sc_irq_mask |= GINTMSK_USBSUSPMSK;
		DWC_OTG_WRITE_4(sc, DOTG_GINTMSK, sc->sc_irq_mask);

		/* complete root HUB interrupt endpoint */
		dwc_otg_root_intr(sc);
	}

	if (status & GINTSTS_PRTINT) {
		uint32_t hprt;

		hprt = DWC_OTG_READ_4(sc, DOTG_HPRT);

		/* clear change bits */
		DWC_OTG_WRITE_4(sc, DOTG_HPRT, (hprt & (
		    HPRT_PRTPWR | HPRT_PRTENCHNG |
		    HPRT_PRTCONNDET | HPRT_PRTOVRCURRCHNG)) |
		    sc->sc_hprt_val);

		DPRINTFN(12, "GINTSTS=0x%08x, HPRT=0x%08x\n", status, hprt);

		sc->sc_flags.status_device_mode = 0;

		if (hprt & HPRT_PRTCONNSTS)
			sc->sc_flags.status_bus_reset = 1;
		else
			sc->sc_flags.status_bus_reset = 0;

		if ((hprt & HPRT_PRTENCHNG) &&
		    (hprt & HPRT_PRTENA) == 0)
			sc->sc_flags.change_enabled = 1;

		if (hprt & HPRT_PRTENA)
			sc->sc_flags.port_enabled = 1;
		else
			sc->sc_flags.port_enabled = 0;

		if (hprt & HPRT_PRTOVRCURRCHNG)
			sc->sc_flags.change_over_current = 1;

		if (hprt & HPRT_PRTOVRCURRACT)
			sc->sc_flags.port_over_current = 1;
		else
			sc->sc_flags.port_over_current = 0;

		if (hprt & HPRT_PRTPWR)
			sc->sc_flags.port_powered = 1;
		else
			sc->sc_flags.port_powered = 0;

		if (((hprt & HPRT_PRTSPD_MASK)
		    >> HPRT_PRTSPD_SHIFT) == HPRT_PRTSPD_LOW)
			sc->sc_flags.status_low_speed = 1;
		else
			sc->sc_flags.status_low_speed = 0;

		if (((hprt & HPRT_PRTSPD_MASK)
		    >> HPRT_PRTSPD_SHIFT) == HPRT_PRTSPD_HIGH)
			sc->sc_flags.status_high_speed = 1;
		else
			sc->sc_flags.status_high_speed = 0;

		if (hprt & HPRT_PRTCONNDET)
			sc->sc_flags.change_connect = 1;

		if (hprt & HPRT_PRTSUSP)
			dwc_otg_suspend_irq(sc);
		else
			dwc_otg_resume_irq(sc);

		/* complete root HUB interrupt endpoint */
		dwc_otg_root_intr(sc);

		/* update host frame interval */
		dwc_otg_update_host_frame_interval(sc);
	}

	/*
	 * If resume and suspend is set at the same time we interpret
	 * that like RESUME. Resume is set when there is at least 3
	 * milliseconds of inactivity on the USB BUS.
	 */
	if (status & GINTSTS_WKUPINT) {

		DPRINTFN(5, "resume interrupt\n");

		dwc_otg_resume_irq(sc);

	} else if (status & GINTSTS_USBSUSP) {

		DPRINTFN(5, "suspend interrupt\n");

		dwc_otg_suspend_irq(sc);
	}
	/* check VBUS */
	if (status & (GINTSTS_USBSUSP |
	    GINTSTS_USBRST |
	    GINTMSK_OTGINTMSK |
	    GINTSTS_SESSREQINT)) {
		uint32_t temp;

		temp = DWC_OTG_READ_4(sc, DOTG_GOTGCTL);

		DPRINTFN(5, "GOTGCTL=0x%08x\n", temp);

		dwc_otg_vbus_interrupt(sc,
		    (temp & (GOTGCTL_ASESVLD | GOTGCTL_BSESVLD)) ? 1 : 0);
	}

	if (sc->sc_xfer_complete != 0) {
		sc->sc_xfer_complete = 0;

		/* complete FIFOs, if any */
		dwc_otg_interrupt_complete_locked(sc);
	}
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
	USB_BUS_UNLOCK(&sc->sc_bus);
}
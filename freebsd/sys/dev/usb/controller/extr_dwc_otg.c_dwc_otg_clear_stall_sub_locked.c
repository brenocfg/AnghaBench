#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct dwc_otg_softc {unsigned int sc_active_rx_ep; int* sc_in_ctl; int* sc_out_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIEPCTL_EPTYPE_BULK ; 
 int /*<<< orphan*/  DIEPCTL_EPTYPE_INTERRUPT ; 
 int /*<<< orphan*/  DIEPCTL_EPTYPE_ISOC ; 
 int DIEPCTL_EPTYPE_SET (int /*<<< orphan*/ ) ; 
 int DIEPCTL_MPS_SET (int) ; 
 int DIEPCTL_SNAK ; 
 int DIEPCTL_TXFNUM_SET (scalar_t__) ; 
 int DIEPCTL_USBACTEP ; 
 int DOEPCTL_EPDIS ; 
 int DOEPCTL_SETD0PID ; 
 int DOTG_DIEPCTL (scalar_t__) ; 
 int DOTG_DIEPTSIZ (scalar_t__) ; 
 int DOTG_DOEPCTL (scalar_t__) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int,int) ; 
 int GRSTCTL_TXFFLSH ; 
 int GRSTCTL_TXFIFO (scalar_t__) ; 
 scalar_t__ UE_BULK ; 
 scalar_t__ UE_CONTROL ; 
 scalar_t__ UE_INTERRUPT ; 
 int /*<<< orphan*/  dwc_otg_interrupt_complete_locked (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_interrupt_poll_locked (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_tx_fifo_reset (struct dwc_otg_softc*,int) ; 

__attribute__((used)) static void
dwc_otg_clear_stall_sub_locked(struct dwc_otg_softc *sc, uint32_t mps,
    uint8_t ep_no, uint8_t ep_type, uint8_t ep_dir)
{
	uint32_t reg;
	uint32_t temp;

	if (ep_type == UE_CONTROL) {
		/* clearing stall is not needed */
		return;
	}

	if (ep_dir) {
		reg = DOTG_DIEPCTL(ep_no);
	} else {
		reg = DOTG_DOEPCTL(ep_no);
		sc->sc_active_rx_ep |= (1U << ep_no);
	}

	/* round up and mask away the multiplier count */
	mps = (mps + 3) & 0x7FC;

	if (ep_type == UE_BULK) {
		temp = DIEPCTL_EPTYPE_SET(
		    DIEPCTL_EPTYPE_BULK) |
		    DIEPCTL_USBACTEP;
	} else if (ep_type == UE_INTERRUPT) {
		temp = DIEPCTL_EPTYPE_SET(
		    DIEPCTL_EPTYPE_INTERRUPT) |
		    DIEPCTL_USBACTEP;
	} else {
		temp = DIEPCTL_EPTYPE_SET(
		    DIEPCTL_EPTYPE_ISOC) |
		    DIEPCTL_USBACTEP;
	}

	temp |= DIEPCTL_MPS_SET(mps);
	temp |= DIEPCTL_TXFNUM_SET(ep_no);

	if (ep_dir)
		sc->sc_in_ctl[ep_no] = temp;
	else
		sc->sc_out_ctl[ep_no] = temp;

	DWC_OTG_WRITE_4(sc, reg, temp | DOEPCTL_EPDIS);
	DWC_OTG_WRITE_4(sc, reg, temp | DOEPCTL_SETD0PID);
	DWC_OTG_WRITE_4(sc, reg, temp | DIEPCTL_SNAK);

	/* we only reset the transmit FIFO */
	if (ep_dir) {
		dwc_otg_tx_fifo_reset(sc,
		    GRSTCTL_TXFIFO(ep_no) |
		    GRSTCTL_TXFFLSH);

		DWC_OTG_WRITE_4(sc,
		    DOTG_DIEPTSIZ(ep_no), 0);
	}

	/* poll interrupt */
	dwc_otg_interrupt_poll_locked(sc);
	dwc_otg_interrupt_complete_locked(sc);
}
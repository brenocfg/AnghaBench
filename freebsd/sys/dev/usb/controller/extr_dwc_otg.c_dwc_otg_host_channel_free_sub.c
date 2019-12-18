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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct dwc_otg_td {scalar_t__* channel; } ;
struct dwc_otg_softc {scalar_t__ sc_last_rx_status; int sc_active_rx_ep; TYPE_1__* sc_chan_state; } ;
struct TYPE_2__ {scalar_t__ wait_halted; scalar_t__ allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_HCCHAR (size_t) ; 
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 scalar_t__ DWC_OTG_MAX_CHANNELS ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 size_t GRXSTSRD_CHNUM_GET (scalar_t__) ; 
 int HCCHAR_CHDIS ; 
 int HCCHAR_CHENA ; 
 int /*<<< orphan*/  dwc_otg_common_rx_ack (struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_host_channel_free_sub(struct dwc_otg_softc *sc, struct dwc_otg_td *td, uint8_t index)
{
	uint32_t hcchar;
	uint8_t x;

	if (td->channel[index] >= DWC_OTG_MAX_CHANNELS)
		return;		/* already freed */

	/* free channel */
	x = td->channel[index];
	td->channel[index] = DWC_OTG_MAX_CHANNELS;

	DPRINTF("CH=%d\n", x);

	/*
	 * We need to let programmed host channels run till complete
	 * else the host channel will stop functioning.
	 */
	sc->sc_chan_state[x].allocated = 0;

	/* ack any pending messages */
	if (sc->sc_last_rx_status != 0 &&
	    GRXSTSRD_CHNUM_GET(sc->sc_last_rx_status) == x) {
		dwc_otg_common_rx_ack(sc);
	}

	/* clear active channel */
	sc->sc_active_rx_ep &= ~(1 << x);

	/* check if already halted */
	if (sc->sc_chan_state[x].wait_halted == 0)
		return;

	/* disable host channel */
	hcchar = DWC_OTG_READ_4(sc, DOTG_HCCHAR(x));
	if (hcchar & HCCHAR_CHENA) {
		DPRINTF("Halting channel %d\n", x);
		DWC_OTG_WRITE_4(sc, DOTG_HCCHAR(x),
		    hcchar | HCCHAR_CHDIS);
		/* don't write HCCHAR until the channel is halted */
	} else {
		sc->sc_chan_state[x].wait_halted = 0;
	}
}
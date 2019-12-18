#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct dwc_otg_td {void** channel; int max_packet_count; int /*<<< orphan*/  hcsplt; int /*<<< orphan*/  hcchar; int /*<<< orphan*/  pc; } ;
struct dwc_otg_softc {int sc_host_ch_max; int sc_active_rx_ep; TYPE_2__* sc_chan_state; } ;
struct TYPE_4__ {scalar_t__ self_suspended; } ;
struct TYPE_6__ {TYPE_1__ flags; } ;
struct TYPE_5__ {int allocated; int wait_halted; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* DWC_OTG_MAX_CHANNELS ; 
 TYPE_3__* DWC_OTG_PC2UDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_clear_hcint (struct dwc_otg_softc*,int) ; 
 int /*<<< orphan*/  dwc_otg_enable_sof_irq (struct dwc_otg_softc*) ; 
 scalar_t__ dwc_otg_host_check_tx_fifo_empty (struct dwc_otg_softc*,struct dwc_otg_td*) ; 

__attribute__((used)) static uint8_t
dwc_otg_host_channel_alloc(struct dwc_otg_softc *sc,
    struct dwc_otg_td *td, uint8_t is_out)
{
	uint8_t x;
	uint8_t y;
	uint8_t z;

	if (td->channel[0] < DWC_OTG_MAX_CHANNELS)
		return (0);		/* already allocated */

	/* check if device is suspended */
	if (DWC_OTG_PC2UDEV(td->pc)->flags.self_suspended != 0)
		return (1);		/* busy - cannot transfer data */

	/* compute needed TX FIFO size */
	if (is_out != 0) {
		if (dwc_otg_host_check_tx_fifo_empty(sc, td) != 0)
			return (1);	/* busy - cannot transfer data */
	}
	z = td->max_packet_count;
	for (x = y = 0; x != sc->sc_host_ch_max; x++) {
		/* check if channel is allocated */
		if (sc->sc_chan_state[x].allocated != 0)
			continue;
		/* check if channel is still enabled */
		if (sc->sc_chan_state[x].wait_halted != 0)
			continue;
		/* store channel number */
		td->channel[y++] = x;
		/* check if we got all channels */
		if (y == z)
			break;
	}
	if (y != z) {
		/* reset channel variable */
		td->channel[0] = DWC_OTG_MAX_CHANNELS;
		td->channel[1] = DWC_OTG_MAX_CHANNELS;
		td->channel[2] = DWC_OTG_MAX_CHANNELS;
		/* wait a bit */
		dwc_otg_enable_sof_irq(sc);
		return (1);	/* busy - not enough channels */
	}

	for (y = 0; y != z; y++) {
		x = td->channel[y];

		/* set allocated */
		sc->sc_chan_state[x].allocated = 1;

		/* set wait halted */
		sc->sc_chan_state[x].wait_halted = 1;

		/* clear interrupts */
		dwc_otg_clear_hcint(sc, x);

		DPRINTF("CH=%d HCCHAR=0x%08x "
		    "HCSPLT=0x%08x\n", x, td->hcchar, td->hcsplt);

		/* set active channel */
		sc->sc_active_rx_ep |= (1 << x);
	}
	return (0);	/* allocated */
}
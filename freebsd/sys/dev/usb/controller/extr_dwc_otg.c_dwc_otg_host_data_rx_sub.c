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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dwc_otg_td {int short_pkt; int got_short; int error_any; int toggle; int /*<<< orphan*/  offset; int /*<<< orphan*/  remainder; int /*<<< orphan*/  pc; int /*<<< orphan*/  tt_scheduled; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  tt_xactpos; int /*<<< orphan*/  ep_type; scalar_t__ state; } ;
struct dwc_otg_softc {int sc_last_rx_status; TYPE_1__* sc_chan_state; } ;
struct TYPE_2__ {int hcint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 scalar_t__ DWC_OTG_MAX_CHANNELS ; 
 int /*<<< orphan*/  GRXSTSRD_BCNT_GET (int) ; 
 scalar_t__ GRXSTSRD_CHNUM_GET (int) ; 
 int GRXSTSRD_DPID_DATA0 ; 
 int GRXSTSRD_DPID_MASK ; 
 int GRXSTSRD_PKTSTS_MASK ; 
#define  GRXSTSRH_IN_DATA 128 
 int HCINT_SOFTWARE_ONLY ; 
 int /*<<< orphan*/  HCSPLT_XACTPOS_BEGIN ; 
 int /*<<< orphan*/  HCSPLT_XACTPOS_MIDDLE ; 
 int /*<<< orphan*/  UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  dwc_otg_common_rx_ack (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_read_fifo (struct dwc_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
dwc_otg_host_data_rx_sub(struct dwc_otg_softc *sc, struct dwc_otg_td *td,
    uint8_t channel)
{
	uint32_t count;

	/* check endpoint status */
	if (sc->sc_last_rx_status == 0)
		goto busy;

	if (channel >= DWC_OTG_MAX_CHANNELS)
		goto busy;

	if (GRXSTSRD_CHNUM_GET(sc->sc_last_rx_status) != channel)
		goto busy;

	switch (sc->sc_last_rx_status & GRXSTSRD_PKTSTS_MASK) {
	case GRXSTSRH_IN_DATA:

		DPRINTF("DATA ST=%d STATUS=0x%08x\n",
		    (int)td->state, (int)sc->sc_last_rx_status);

		if (sc->sc_chan_state[channel].hcint & HCINT_SOFTWARE_ONLY) {
			/*
			 * When using SPLIT transactions on interrupt
			 * endpoints, sometimes data occurs twice.
			 */
			DPRINTF("Data already received\n");
			break;
		}

		/* get the packet byte count */
		count = GRXSTSRD_BCNT_GET(sc->sc_last_rx_status);

		/* check for ISOCHRONOUS endpoint */
		if (td->ep_type == UE_ISOCHRONOUS) {
			if ((sc->sc_last_rx_status & GRXSTSRD_DPID_MASK) !=
			    GRXSTSRD_DPID_DATA0) {
				/* more data to be received */
				td->tt_xactpos = HCSPLT_XACTPOS_MIDDLE;
			} else {
				/* all data received */
				td->tt_xactpos = HCSPLT_XACTPOS_BEGIN;
				/* verify the packet byte count */
				if (count != td->remainder) {
					/* we have a short packet */
					td->short_pkt = 1;
					td->got_short = 1;
				}
			}
		} else {
			/* verify the packet byte count */
			if (count != td->max_packet_size) {
				if (count < td->max_packet_size) {
					/* we have a short packet */
					td->short_pkt = 1;
					td->got_short = 1;
				} else {
					/* invalid USB packet */
					td->error_any = 1;
			  
					/* release FIFO */
					dwc_otg_common_rx_ack(sc);
					goto complete;
				}
			}
			td->toggle ^= 1;
			td->tt_scheduled = 0;
		}

		/* verify the packet byte count */
		if (count > td->remainder) {
			/* invalid USB packet */
			td->error_any = 1;

			/* release FIFO */
			dwc_otg_common_rx_ack(sc);
			goto complete;
		}

		/* read data from FIFO */
		dwc_otg_read_fifo(sc, td->pc, td->offset, count);

		td->remainder -= count;
		td->offset += count;
		sc->sc_chan_state[channel].hcint |= HCINT_SOFTWARE_ONLY;
		break;
	default:
		break;
	}
	/* release FIFO */
	dwc_otg_common_rx_ack(sc);
busy:
	return (0);
complete:
	return (1);
}
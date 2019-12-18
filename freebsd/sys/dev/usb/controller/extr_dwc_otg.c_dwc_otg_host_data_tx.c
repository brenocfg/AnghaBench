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
struct dwc_otg_td {size_t* channel; size_t npkt; int state; int error_stall; int error_any; int errcnt; int hcsplt; int did_nak; scalar_t__ tt_scheduled; scalar_t__ offset; scalar_t__ tx_bytes; scalar_t__ remainder; int toggle; int short_pkt; size_t tt_start_slot; scalar_t__ ep_type; size_t max_packet_count; int max_packet_size; int hcchar; int tt_complete_slot; int /*<<< orphan*/  pc; scalar_t__ set_toggle; } ;
struct dwc_otg_softc {size_t sc_last_frame_num; TYPE_1__* sc_chan_state; } ;
struct TYPE_2__ {int hcint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_DFIFO (size_t) ; 
 int /*<<< orphan*/  DOTG_HCCHAR (size_t) ; 
 int /*<<< orphan*/  DOTG_HCSPLT (size_t) ; 
 int /*<<< orphan*/  DOTG_HCTSIZ (size_t) ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
#define  DWC_CHAN_ST_START 133 
#define  DWC_CHAN_ST_TX_WAIT_ISOC 132 
#define  DWC_CHAN_ST_WAIT_ANE 131 
#define  DWC_CHAN_ST_WAIT_C_ANE 130 
#define  DWC_CHAN_ST_WAIT_C_PKT 129 
#define  DWC_CHAN_ST_WAIT_S_ANE 128 
 size_t DWC_OTG_MAX_CHANNELS ; 
 int /*<<< orphan*/  DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 size_t DWC_OTG_TT_SLOT_MAX ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int HCCHAR_EPDIR_IN ; 
 int HCCHAR_ODDFRM ; 
 int HCINT_ACK ; 
 int HCINT_ERRORS ; 
 int HCINT_HCH_DONE_MASK ; 
 int HCINT_NYET ; 
 int HCINT_RETRY ; 
 int HCINT_STALL ; 
 int HCSPLT_COMPSPLT ; 
 int HCSPLT_XACTLEN_BURST ; 
 int HCSPLT_XACTPOS_ALL ; 
 int HCSPLT_XACTPOS_MASK ; 
 int HCSPLT_XACTPOS_SHIFT ; 
 int HCTSIZ_PID_DATA0 ; 
 int HCTSIZ_PID_DATA1 ; 
 int HCTSIZ_PID_DATA2 ; 
 int HCTSIZ_PID_MDATA ; 
 int HCTSIZ_PID_SHIFT ; 
 int HCTSIZ_PKTCNT_SHIFT ; 
 int HCTSIZ_XFERSIZE_SHIFT ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 scalar_t__ dwc_otg_host_channel_alloc (struct dwc_otg_softc*,struct dwc_otg_td*,int) ; 
 int /*<<< orphan*/  dwc_otg_host_channel_free (struct dwc_otg_softc*,struct dwc_otg_td*) ; 
 int /*<<< orphan*/  dwc_otg_host_dump_rx (struct dwc_otg_softc*,struct dwc_otg_td*) ; 
 scalar_t__ dwc_otg_host_rate_check (struct dwc_otg_softc*,struct dwc_otg_td*) ; 
 int /*<<< orphan*/  dwc_otg_write_fifo (struct dwc_otg_softc*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
dwc_otg_host_data_tx(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint32_t count;
	uint32_t hcint;
	uint32_t hcchar;
	uint8_t delta;
	uint8_t channel;
	uint8_t x;

	dwc_otg_host_dump_rx(sc, td);

	/* check that last channel is complete */
	channel = td->channel[td->npkt];

	if (channel < DWC_OTG_MAX_CHANNELS) {
		hcint = sc->sc_chan_state[channel].hcint;

		DPRINTF("CH=%d ST=%d HCINT=0x%08x HCCHAR=0x%08x HCTSIZ=0x%08x\n",
		    channel, td->state, hcint,
		    DWC_OTG_READ_4(sc, DOTG_HCCHAR(channel)),
		    DWC_OTG_READ_4(sc, DOTG_HCTSIZ(channel)));

		if (hcint & (HCINT_RETRY |
		    HCINT_ACK | HCINT_NYET)) {
			/* give success bits priority over failure bits */
		} else if (hcint & HCINT_STALL) {
			DPRINTF("CH=%d STALL\n", channel);
			td->error_stall = 1;
			td->error_any = 1;
			goto complete;
		} else if (hcint & HCINT_ERRORS) {
			DPRINTF("CH=%d ERROR\n", channel);
			td->errcnt++;
			if (td->hcsplt != 0 || td->errcnt >= 3) {
				td->error_any = 1;
				goto complete;
			}
		}

		if (hcint & (HCINT_ERRORS | HCINT_RETRY |
		    HCINT_ACK | HCINT_NYET)) {

			if (!(hcint & HCINT_ERRORS))
				td->errcnt = 0;
		}
	} else {
		hcint = 0;
	}

	switch (td->state) {
	case DWC_CHAN_ST_START:
		goto send_pkt;

	case DWC_CHAN_ST_WAIT_ANE:
		if (hcint & (HCINT_RETRY | HCINT_ERRORS)) {
			td->did_nak = 1;
			td->tt_scheduled = 0;
			goto send_pkt;
		} else if (hcint & (HCINT_ACK | HCINT_NYET)) {
			td->offset += td->tx_bytes;
			td->remainder -= td->tx_bytes;
			td->toggle ^= 1;
			/* check if next response will be a NAK */
			if (hcint & HCINT_NYET)
				td->did_nak = 1;
			else
				td->did_nak = 0;
			td->tt_scheduled = 0;

			/* check remainder */
			if (td->remainder == 0) {
				if (td->short_pkt)
					goto complete;

				/*
				 * Else we need to transmit a short
				 * packet:
				 */
			}
			goto send_pkt;
		}
		break;

	case DWC_CHAN_ST_WAIT_S_ANE:
		if (hcint & (HCINT_RETRY | HCINT_ERRORS)) {
			td->did_nak = 1;
			td->tt_scheduled = 0;
			goto send_pkt;
		} else if (hcint & (HCINT_ACK | HCINT_NYET)) {
			td->did_nak = 0;
			goto send_cpkt;
		}
		break;

	case DWC_CHAN_ST_WAIT_C_ANE:
		if (hcint & HCINT_NYET) {
			goto send_cpkt;
		} else if (hcint & (HCINT_RETRY | HCINT_ERRORS)) {
			td->did_nak = 1;
			td->tt_scheduled = 0;
			goto send_pkt;
		} else if (hcint & HCINT_ACK) {
			td->offset += td->tx_bytes;
			td->remainder -= td->tx_bytes;
			td->toggle ^= 1;
			td->did_nak = 0;
			td->tt_scheduled = 0;

			/* check remainder */
			if (td->remainder == 0) {
				if (td->short_pkt)
					goto complete;

				/* else we need to transmit a short packet */
			}
			goto send_pkt;
		}
		break;

	case DWC_CHAN_ST_WAIT_C_PKT:
		goto send_cpkt;

	case DWC_CHAN_ST_TX_WAIT_ISOC:
		/* Check if ISOCHRONOUS OUT traffic is complete */
		if ((hcint & HCINT_HCH_DONE_MASK) == 0)
			break;

		td->offset += td->tx_bytes;
		td->remainder -= td->tx_bytes;
		goto complete;
	default:
		break;
	}
	goto busy;

send_pkt:
	/* free existing channel(s), if any */
	dwc_otg_host_channel_free(sc, td);

	if (td->hcsplt != 0) {
		delta = td->tt_start_slot - sc->sc_last_frame_num - 1;
		if (td->tt_scheduled == 0 || delta < DWC_OTG_TT_SLOT_MAX) {
			td->state = DWC_CHAN_ST_START;
			goto busy;
		}
		delta = sc->sc_last_frame_num - td->tt_start_slot;
		if (delta > 5) {
			/* missed it */
			td->tt_scheduled = 0;
			td->state = DWC_CHAN_ST_START;
			goto busy;
		}
	} else if (dwc_otg_host_rate_check(sc, td)) {
		td->state = DWC_CHAN_ST_START;
		goto busy;
	}

	/* allocate a new channel */
	if (dwc_otg_host_channel_alloc(sc, td, 1)) {
		td->state = DWC_CHAN_ST_START;
		goto busy;
	}

	/* set toggle, if any */
	if (td->set_toggle) {
		td->set_toggle = 0;
		td->toggle = 1;
	}

	if (td->ep_type == UE_ISOCHRONOUS) {
		/* ISOCHRONOUS OUT transfers don't have any ACKs */
		td->state = DWC_CHAN_ST_TX_WAIT_ISOC;
		td->hcsplt &= ~HCSPLT_COMPSPLT;
		if (td->hcsplt != 0) {
			/* get maximum transfer length */
			count = td->remainder;
			if (count > HCSPLT_XACTLEN_BURST) {
				DPRINTF("TT overflow\n");
				td->error_any = 1;
				goto complete;
			}
			/* Update transaction position */
			td->hcsplt &= ~HCSPLT_XACTPOS_MASK;
			td->hcsplt |= (HCSPLT_XACTPOS_ALL << HCSPLT_XACTPOS_SHIFT);
		}
	} else if (td->hcsplt != 0) {
		td->hcsplt &= ~HCSPLT_COMPSPLT;
		/* Wait for ACK/NAK/ERR from TT */
		td->state = DWC_CHAN_ST_WAIT_S_ANE;
	} else {
		/* Wait for ACK/NAK/STALL from device */
		td->state = DWC_CHAN_ST_WAIT_ANE;
	}

	td->tx_bytes = 0;
	
	for (x = 0; x != td->max_packet_count; x++) {
		uint32_t rem_bytes;

		channel = td->channel[x];

		/* send one packet at a time */
		count = td->max_packet_size;
		rem_bytes = td->remainder - td->tx_bytes;
		if (rem_bytes < count) {
			/* we have a short packet */
			td->short_pkt = 1;
			count = rem_bytes;
		}
		if (count == rem_bytes) {
			/* last packet */
			switch (x) {
			case 0:
				DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
				    (count << HCTSIZ_XFERSIZE_SHIFT) |
				    (1 << HCTSIZ_PKTCNT_SHIFT) |
				    (td->toggle ? (HCTSIZ_PID_DATA1 << HCTSIZ_PID_SHIFT) :
				    (HCTSIZ_PID_DATA0 << HCTSIZ_PID_SHIFT)));
				break;
			case 1:
				DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
				    (count << HCTSIZ_XFERSIZE_SHIFT) |
				    (1 << HCTSIZ_PKTCNT_SHIFT) |
				    (HCTSIZ_PID_DATA1 << HCTSIZ_PID_SHIFT));
				break;
			default:
				DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
				    (count << HCTSIZ_XFERSIZE_SHIFT) |
				    (1 << HCTSIZ_PKTCNT_SHIFT) |
				    (HCTSIZ_PID_DATA2 << HCTSIZ_PID_SHIFT));
				break;
			}
		} else if (td->ep_type == UE_ISOCHRONOUS &&
			   td->max_packet_count > 1) {
			/* ISOCHRONOUS multi packet */
			DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
			    (count << HCTSIZ_XFERSIZE_SHIFT) |
			    (1 << HCTSIZ_PKTCNT_SHIFT) |
			    (HCTSIZ_PID_MDATA << HCTSIZ_PID_SHIFT));
		} else {
			/* TODO: HCTSIZ_DOPNG */
			/* standard BULK/INTERRUPT/CONTROL packet */
			DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
			    (count << HCTSIZ_XFERSIZE_SHIFT) |
			    (1 << HCTSIZ_PKTCNT_SHIFT) |
			    (td->toggle ? (HCTSIZ_PID_DATA1 << HCTSIZ_PID_SHIFT) :
			    (HCTSIZ_PID_DATA0 << HCTSIZ_PID_SHIFT)));
		}

		DWC_OTG_WRITE_4(sc, DOTG_HCSPLT(channel), td->hcsplt);

		hcchar = td->hcchar;
		hcchar &= ~HCCHAR_EPDIR_IN;

		/* send after next SOF event */
		if ((sc->sc_last_frame_num & 1) == 0 &&
		    td->ep_type == UE_ISOCHRONOUS)
			hcchar |= HCCHAR_ODDFRM;
		else
			hcchar &= ~HCCHAR_ODDFRM;

		/* must enable before writing data to FIFO */
		DWC_OTG_WRITE_4(sc, DOTG_HCCHAR(channel), hcchar);

		if (count != 0) {
			/* write data into FIFO */
			dwc_otg_write_fifo(sc, td->pc, td->offset +
			    td->tx_bytes, DOTG_DFIFO(channel), count);
		}

		/* store number of bytes transmitted */
		td->tx_bytes += count;

		/* store last packet index */
		td->npkt = x;
		
		/* check for last packet */
		if (count == rem_bytes)
			break;
	}
	goto busy;

send_cpkt:
	/* free existing channel, if any */
	dwc_otg_host_channel_free(sc, td);

	delta = td->tt_complete_slot - sc->sc_last_frame_num - 1;
	if (td->tt_scheduled == 0 || delta < DWC_OTG_TT_SLOT_MAX) {
		td->state = DWC_CHAN_ST_WAIT_C_PKT;
		goto busy;
	}
	delta = sc->sc_last_frame_num - td->tt_start_slot;
	if (delta > DWC_OTG_TT_SLOT_MAX) {
		/* we missed the service interval */
		if (td->ep_type != UE_ISOCHRONOUS)
			td->error_any = 1;
		goto complete;
	}

	/* allocate a new channel */
	if (dwc_otg_host_channel_alloc(sc, td, 0)) {
		td->state = DWC_CHAN_ST_WAIT_C_PKT;
		goto busy;
	}

	channel = td->channel[0];

 	td->hcsplt |= HCSPLT_COMPSPLT;
	td->state = DWC_CHAN_ST_WAIT_C_ANE;

	DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
	    (HCTSIZ_PID_DATA0 << HCTSIZ_PID_SHIFT));

	DWC_OTG_WRITE_4(sc, DOTG_HCSPLT(channel), td->hcsplt);

	hcchar = td->hcchar;
	hcchar &= ~HCCHAR_EPDIR_IN;

	/* receive complete split ASAP */
	if ((sc->sc_last_frame_num & 1) != 0 &&
	    td->ep_type == UE_ISOCHRONOUS)
		hcchar |= HCCHAR_ODDFRM;
	else
		hcchar &= ~HCCHAR_ODDFRM;

	/* must enable channel before data can be received */
	DWC_OTG_WRITE_4(sc, DOTG_HCCHAR(channel), hcchar);

	/* wait until next slot before trying complete split */
	td->tt_complete_slot = sc->sc_last_frame_num + 1;
busy:
	return (1);	/* busy */

complete:
	dwc_otg_host_channel_free(sc, td);
	return (0);	/* complete */
}
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
struct dwc_otg_td {size_t max_packet_count; size_t* channel; int state; int error_stall; int error_any; int errcnt; int hcsplt; scalar_t__ ep_type; int toggle; int did_nak; scalar_t__ tt_scheduled; size_t tt_complete_slot; size_t tt_start_slot; int max_packet_size; int hcchar; scalar_t__ set_toggle; int /*<<< orphan*/  short_pkt; int /*<<< orphan*/  got_short; int /*<<< orphan*/  remainder; int /*<<< orphan*/  tt_xactpos; } ;
struct dwc_otg_softc {size_t sc_last_frame_num; TYPE_1__* sc_chan_state; } ;
struct TYPE_2__ {int hcint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_HCCHAR (size_t) ; 
 int /*<<< orphan*/  DOTG_HCSPLT (size_t) ; 
 int /*<<< orphan*/  DOTG_HCTSIZ (size_t) ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
#define  DWC_CHAN_ST_START 131 
#define  DWC_CHAN_ST_WAIT_ANE 130 
#define  DWC_CHAN_ST_WAIT_C_PKT 129 
#define  DWC_CHAN_ST_WAIT_S_ANE 128 
 size_t DWC_OTG_MAX_CHANNELS ; 
 int /*<<< orphan*/  DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 size_t DWC_OTG_TT_SLOT_MAX ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int HCCHAR_EPDIR_IN ; 
 int HCCHAR_ODDFRM ; 
 int HCINT_ACK ; 
 int HCINT_DATATGLERR ; 
 int HCINT_ERRORS ; 
 int HCINT_NYET ; 
 int HCINT_RETRY ; 
 int HCINT_SOFTWARE_ONLY ; 
 int HCINT_STALL ; 
 int HCSPLT_COMPSPLT ; 
 int /*<<< orphan*/  HCSPLT_XACTPOS_BEGIN ; 
 int HCTSIZ_PID_DATA0 ; 
 int HCTSIZ_PID_DATA1 ; 
 int HCTSIZ_PID_SHIFT ; 
 int HCTSIZ_PKTCNT_SHIFT ; 
 int HCTSIZ_XFERSIZE_SHIFT ; 
 scalar_t__ UE_INTERRUPT ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 scalar_t__ dwc_otg_host_channel_alloc (struct dwc_otg_softc*,struct dwc_otg_td*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_host_channel_free (struct dwc_otg_softc*,struct dwc_otg_td*) ; 
 scalar_t__ dwc_otg_host_data_rx_sub (struct dwc_otg_softc*,struct dwc_otg_td*,size_t) ; 
 scalar_t__ dwc_otg_host_rate_check (struct dwc_otg_softc*,struct dwc_otg_td*) ; 

__attribute__((used)) static uint8_t
dwc_otg_host_data_rx(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint32_t hcint = 0;
	uint32_t hcchar;
	uint8_t delta;
	uint8_t channel;
	uint8_t x;

	for (x = 0; x != td->max_packet_count; x++) {
		channel = td->channel[x];
		if (channel >= DWC_OTG_MAX_CHANNELS)
			continue;
		hcint |= sc->sc_chan_state[channel].hcint;

		DPRINTF("CH=%d ST=%d HCINT=0x%08x HCCHAR=0x%08x HCTSIZ=0x%08x\n",
		    channel, td->state, hcint,
		    DWC_OTG_READ_4(sc, DOTG_HCCHAR(channel)),
		    DWC_OTG_READ_4(sc, DOTG_HCTSIZ(channel)));

		/* check interrupt bits */
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
				if (td->ep_type != UE_ISOCHRONOUS) {
					td->error_any = 1;
					goto complete;
				}
			}
		}

		/* check channels for data, if any */
		if (dwc_otg_host_data_rx_sub(sc, td, channel))
			goto complete;

		/* refresh interrupt status */
		hcint |= sc->sc_chan_state[channel].hcint;

		if (hcint & (HCINT_ERRORS | HCINT_RETRY |
		    HCINT_ACK | HCINT_NYET)) {
			if (!(hcint & HCINT_ERRORS))
				td->errcnt = 0;
		}
	}

	switch (td->state) {
	case DWC_CHAN_ST_START:
		if (td->hcsplt != 0)
			goto receive_spkt;
		else
			goto receive_pkt;

	case DWC_CHAN_ST_WAIT_ANE:
		if (hcint & (HCINT_RETRY | HCINT_ERRORS)) {
			if (td->ep_type == UE_INTERRUPT) {
				/*
				 * The USB specification does not
				 * mandate a particular data toggle
				 * value for USB INTERRUPT
				 * transfers. Switch the data toggle
				 * value to receive the packet
				 * correctly:
				 */
				if (hcint & HCINT_DATATGLERR) {
					DPRINTF("Retrying packet due to "
					    "data toggle error\n");
					td->toggle ^= 1;
					goto receive_pkt;
				}
			} else if (td->ep_type == UE_ISOCHRONOUS) {
				if (td->hcsplt != 0) {
					/*
					 * Sometimes the complete
					 * split packet may be queued
					 * too early and the
					 * transaction translator will
					 * return a NAK. Ignore
					 * this message and retry the
					 * complete split instead.
					 */
					DPRINTF("Retrying complete split\n");
					goto receive_pkt;
				}
				goto complete;
			}
			td->did_nak = 1;
			td->tt_scheduled = 0;
			if (td->hcsplt != 0)
				goto receive_spkt;
			else
				goto receive_pkt;
		} else if (hcint & HCINT_NYET) {
			if (td->hcsplt != 0) {
				/* try again */
				goto receive_pkt;
			} else {
				/* not a valid token for IN endpoints */
				td->error_any = 1;
				goto complete;
			}
		} else if (hcint & HCINT_ACK) {
			/* wait for data - ACK arrived first */
			if (!(hcint & HCINT_SOFTWARE_ONLY))
				goto busy;

			if (td->ep_type == UE_ISOCHRONOUS) {
				/* check if we are complete */
				if (td->tt_xactpos == HCSPLT_XACTPOS_BEGIN) {
					goto complete;
				} else if (td->hcsplt != 0) {
					goto receive_pkt;
				} else {
					/* get more packets */
					goto busy;
				}
			} else {
				/* check if we are complete */
				if ((td->remainder == 0) || (td->got_short != 0)) {
					if (td->short_pkt)
						goto complete;

					/*
					 * Else need to receive a zero length
					 * packet.
					 */
				}
				td->tt_scheduled = 0;
				td->did_nak = 0;
				if (td->hcsplt != 0)
					goto receive_spkt;
				else
					goto receive_pkt;
			}
		}
		break;

	case DWC_CHAN_ST_WAIT_S_ANE:
		/*
		 * NOTE: The DWC OTG hardware provides a fake ACK in
		 * case of interrupt and isochronous transfers:
		 */ 
		if (hcint & (HCINT_RETRY | HCINT_ERRORS)) {
			td->did_nak = 1;
			td->tt_scheduled = 0;
			goto receive_spkt;
		} else if (hcint & HCINT_NYET) {
			td->tt_scheduled = 0;
			goto receive_spkt;
		} else if (hcint & HCINT_ACK) {
			td->did_nak = 0;
			goto receive_pkt;
		}
		break;

	case DWC_CHAN_ST_WAIT_C_PKT:
		goto receive_pkt;

	default:
		break;
	}
	goto busy;

receive_pkt:
	/* free existing channel, if any */
	dwc_otg_host_channel_free(sc, td);

  	if (td->hcsplt != 0) {
		delta = td->tt_complete_slot - sc->sc_last_frame_num - 1;
		if (td->tt_scheduled == 0 || delta < DWC_OTG_TT_SLOT_MAX) {
			if (td->ep_type != UE_ISOCHRONOUS) {
				td->state = DWC_CHAN_ST_WAIT_C_PKT;
				goto busy;
			}
		}
		delta = sc->sc_last_frame_num - td->tt_start_slot;
		if (delta > DWC_OTG_TT_SLOT_MAX) {
			if (td->ep_type != UE_ISOCHRONOUS) {
				/* we missed the service interval */
				td->error_any = 1;
			}
			goto complete;
		}
		/* complete split */
		td->hcsplt |= HCSPLT_COMPSPLT;
	} else if (dwc_otg_host_rate_check(sc, td)) {
		td->state = DWC_CHAN_ST_WAIT_C_PKT;
		goto busy;
	}

	/* allocate a new channel */
	if (dwc_otg_host_channel_alloc(sc, td, 0)) {
		td->state = DWC_CHAN_ST_WAIT_C_PKT;
		goto busy;
	}

	/* set toggle, if any */
	if (td->set_toggle) {
		td->set_toggle = 0;
		td->toggle = 1;
	}

	td->state = DWC_CHAN_ST_WAIT_ANE;

	for (x = 0; x != td->max_packet_count; x++) {
	  	channel = td->channel[x];

		/* receive one packet */
		DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
		    (td->max_packet_size << HCTSIZ_XFERSIZE_SHIFT) |
		    (1 << HCTSIZ_PKTCNT_SHIFT) |
		    (td->toggle ? (HCTSIZ_PID_DATA1 << HCTSIZ_PID_SHIFT) :
		    (HCTSIZ_PID_DATA0 << HCTSIZ_PID_SHIFT)));

		DWC_OTG_WRITE_4(sc, DOTG_HCSPLT(channel), td->hcsplt);

		hcchar = td->hcchar;
		hcchar |= HCCHAR_EPDIR_IN;

		if (td->ep_type == UE_ISOCHRONOUS) {
			if (td->hcsplt != 0) {
				/* continously buffer */
				if (sc->sc_last_frame_num & 1)
					hcchar &= ~HCCHAR_ODDFRM;
				else
					hcchar |= HCCHAR_ODDFRM;
			} else {
				/* multi buffer, if any */
				if (sc->sc_last_frame_num & 1)
					hcchar |= HCCHAR_ODDFRM;
				else
					hcchar &= ~HCCHAR_ODDFRM;
			}
		} else {
			hcchar &= ~HCCHAR_ODDFRM;
		}

		/* must enable channel before data can be received */
		DWC_OTG_WRITE_4(sc, DOTG_HCCHAR(channel), hcchar);
	}
	/* wait until next slot before trying complete split */
	td->tt_complete_slot = sc->sc_last_frame_num + 1;

	goto busy;

receive_spkt:
	/* free existing channel(s), if any */
	dwc_otg_host_channel_free(sc, td);

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

	/* allocate a new channel */
	if (dwc_otg_host_channel_alloc(sc, td, 0)) {
		td->state = DWC_CHAN_ST_START;
		goto busy;
	}

	channel = td->channel[0];

	td->hcsplt &= ~HCSPLT_COMPSPLT;
	td->state = DWC_CHAN_ST_WAIT_S_ANE;

	/* receive one packet */
	DWC_OTG_WRITE_4(sc, DOTG_HCTSIZ(channel),
	    (HCTSIZ_PID_DATA0 << HCTSIZ_PID_SHIFT));

	DWC_OTG_WRITE_4(sc, DOTG_HCSPLT(channel), td->hcsplt);

	/* send after next SOF event */
	if ((sc->sc_last_frame_num & 1) == 0 &&
	    td->ep_type == UE_ISOCHRONOUS)
		td->hcchar |= HCCHAR_ODDFRM;
	else
		td->hcchar &= ~HCCHAR_ODDFRM;

	hcchar = td->hcchar;
	hcchar |= HCCHAR_EPDIR_IN;

	/* wait until next slot before trying complete split */
	td->tt_complete_slot = sc->sc_last_frame_num + 1;

	/* must enable channel before data can be received */
	DWC_OTG_WRITE_4(sc, DOTG_HCCHAR(channel), hcchar);
busy:
	return (1);	/* busy */

complete:
	dwc_otg_host_channel_free(sc, td);
	return (0);	/* complete */
}
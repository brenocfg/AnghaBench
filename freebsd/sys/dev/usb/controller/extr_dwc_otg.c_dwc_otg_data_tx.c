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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct dwc_otg_td {size_t ep_no; int error_any; int tx_bytes; scalar_t__ npkt; scalar_t__ max_packet_size; int offset; int remainder; int short_pkt; int /*<<< orphan*/  pc; } ;
struct dwc_otg_softc {int sc_last_rx_status; int* sc_in_ctl; TYPE_1__* sc_hw_ep_profile; } ;
struct TYPE_2__ {int max_buffer; } ;

/* Variables and functions */
 int DIEPCTL_CNAK ; 
 int DIEPCTL_EPENA ; 
 int DIEPCTL_EPTYPE_ISOC ; 
 int DIEPCTL_EPTYPE_MASK ; 
 int DIEPCTL_EPTYPE_SHIFT ; 
 int DIEPCTL_SETD0PID ; 
 int DIEPCTL_SETD1PID ; 
 int /*<<< orphan*/  DOTG_DFIFO (size_t) ; 
 int /*<<< orphan*/  DOTG_DIEPCTL (size_t) ; 
 int /*<<< orphan*/  DOTG_DIEPTSIZ (size_t) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int,size_t,...) ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DXEPTSIZ_GET_NPKT (int) ; 
 int DXEPTSIZ_SET_MULTI (int) ; 
 int DXEPTSIZ_SET_NBYTES (int) ; 
 int DXEPTSIZ_SET_NPKT (int) ; 
 scalar_t__ GRXSTSRD_CHNUM_GET (int) ; 
 int GRXSTSRD_PKTSTS_MASK ; 
 int GRXSTSRD_STP_COMPLETE ; 
 int GRXSTSRD_STP_DATA ; 
 int /*<<< orphan*/  dwc_otg_common_rx_ack (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_write_fifo (struct dwc_otg_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
dwc_otg_data_tx(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint32_t max_buffer;
	uint32_t count;
	uint32_t fifo_left;
	uint32_t mpkt;
	uint32_t temp;
	uint8_t to;

	to = 3;				/* don't loop forever! */

	max_buffer = sc->sc_hw_ep_profile[td->ep_no].max_buffer;

repeat:
	/* check for for endpoint 0 data */

	temp = sc->sc_last_rx_status;

	if ((td->ep_no == 0) && (temp != 0) &&
	    (GRXSTSRD_CHNUM_GET(temp) == 0)) {

		if ((temp & GRXSTSRD_PKTSTS_MASK) !=
		    GRXSTSRD_STP_DATA &&
		    (temp & GRXSTSRD_PKTSTS_MASK) !=
		    GRXSTSRD_STP_COMPLETE) {

			/* dump data - wrong direction */
			dwc_otg_common_rx_ack(sc);
		} else {
			/*
			 * The current transfer was cancelled
			 * by the USB Host:
			 */
			td->error_any = 1;
			return (0);		/* complete */
		}
	}

	/* fill in more TX data, if possible */
	if (td->tx_bytes != 0) {

		uint16_t cpkt;

		/* check if packets have been transferred */
		temp = DWC_OTG_READ_4(sc, DOTG_DIEPTSIZ(td->ep_no));

		/* get current packet number */
		cpkt = DXEPTSIZ_GET_NPKT(temp);

		if (cpkt >= td->npkt) {
			fifo_left = 0;
		} else {
			if (max_buffer != 0) {
				fifo_left = (td->npkt - cpkt) *
				    td->max_packet_size;

				if (fifo_left > max_buffer)
					fifo_left = max_buffer;
			} else {
				fifo_left = td->max_packet_size;
			}
		}

		count = td->tx_bytes;
		if (count > fifo_left)
			count = fifo_left;

		if (count != 0) {
			/* write data into FIFO */
			dwc_otg_write_fifo(sc, td->pc, td->offset,
			    DOTG_DFIFO(td->ep_no), count);

			td->tx_bytes -= count;
			td->remainder -= count;
			td->offset += count;
			td->npkt = cpkt;
		}
		if (td->tx_bytes != 0)
			goto not_complete;

		/* check remainder */
		if (td->remainder == 0) {
			if (td->short_pkt)
				return (0);	/* complete */

			/* else we need to transmit a short packet */
		}
	}

	if (!to--)
		goto not_complete;

	/* check if not all packets have been transferred */
	temp = DWC_OTG_READ_4(sc, DOTG_DIEPTSIZ(td->ep_no));

	if (DXEPTSIZ_GET_NPKT(temp) != 0) {

		DPRINTFN(5, "busy ep=%d npkt=%d DIEPTSIZ=0x%08x "
		    "DIEPCTL=0x%08x\n", td->ep_no,
		    DXEPTSIZ_GET_NPKT(temp),
		    temp, DWC_OTG_READ_4(sc, DOTG_DIEPCTL(td->ep_no)));

		goto not_complete;
	}

	DPRINTFN(5, "rem=%u ep=%d\n", td->remainder, td->ep_no);

	/* try to optimise by sending more data */
	if ((max_buffer != 0) && ((td->max_packet_size & 3) == 0)) {

		/* send multiple packets at the same time */
		mpkt = max_buffer / td->max_packet_size;

		if (mpkt > 0x3FE)
			mpkt = 0x3FE;

		count = td->remainder;
		if (count > 0x7FFFFF)
			count = 0x7FFFFF - (0x7FFFFF % td->max_packet_size);

		td->npkt = count / td->max_packet_size;

		/*
		 * NOTE: We could use 0x3FE instead of "mpkt" in the
		 * check below to get more throughput, but then we
		 * have a dependency towards non-generic chip features
		 * to disable the TX-FIFO-EMPTY interrupts on a per
		 * endpoint basis. Increase the maximum buffer size of
		 * the IN endpoint to increase the performance.
		 */
		if (td->npkt > mpkt) {
			td->npkt = mpkt;
			count = td->max_packet_size * mpkt;
		} else if ((count == 0) || (count % td->max_packet_size)) {
			/* we are transmitting a short packet */
			td->npkt++;
			td->short_pkt = 1;
		}
	} else {
		/* send one packet at a time */
		mpkt = 1;
		count = td->max_packet_size;
		if (td->remainder < count) {
			/* we have a short packet */
			td->short_pkt = 1;
			count = td->remainder;
		}
		td->npkt = 1;
	}
	DWC_OTG_WRITE_4(sc, DOTG_DIEPTSIZ(td->ep_no),
	    DXEPTSIZ_SET_MULTI(1) |
	    DXEPTSIZ_SET_NPKT(td->npkt) | 
	    DXEPTSIZ_SET_NBYTES(count));

	/* make room for buffering */
	td->npkt += mpkt;

	temp = sc->sc_in_ctl[td->ep_no];

	/* check for isochronous mode */
	if ((temp & DIEPCTL_EPTYPE_MASK) ==
	    (DIEPCTL_EPTYPE_ISOC << DIEPCTL_EPTYPE_SHIFT)) {
		/* toggle odd or even frame bit */
		if (temp & DIEPCTL_SETD1PID) {
			temp &= ~DIEPCTL_SETD1PID;
			temp |= DIEPCTL_SETD0PID;
		} else {
			temp &= ~DIEPCTL_SETD0PID;
			temp |= DIEPCTL_SETD1PID;
		}
		sc->sc_in_ctl[td->ep_no] = temp;
	}

	/* must enable before writing data to FIFO */
	DWC_OTG_WRITE_4(sc, DOTG_DIEPCTL(td->ep_no), temp |
	    DIEPCTL_EPENA | DIEPCTL_CNAK);

	td->tx_bytes = count;

	/* check remainder */
	if (td->tx_bytes == 0 &&
	    td->remainder == 0) {
		if (td->short_pkt)
			return (0);	/* complete */

		/* else we need to transmit a short packet */
	}
	goto repeat;

not_complete:
	return (1);			/* not complete */
}
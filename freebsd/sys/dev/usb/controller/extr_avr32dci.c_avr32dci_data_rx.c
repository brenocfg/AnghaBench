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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct usb_page_search {scalar_t__ length; int /*<<< orphan*/  buffer; } ;
struct avr32dci_td {int ep_no; scalar_t__ remainder; int error; scalar_t__ max_packet_size; int short_pkt; int offset; int bank_shift; int /*<<< orphan*/  pc; } ;
struct avr32dci_softc {scalar_t__ physdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_EPTCLRSTA (int) ; 
 int /*<<< orphan*/  AVR32_EPTSTA (int) ; 
 scalar_t__ AVR32_EPTSTA_BYTE_COUNT (int) ; 
 int AVR32_EPTSTA_CURRENT_BANK (int) ; 
 int AVR32_EPTSTA_RX_BK_RDY ; 
 int AVR32_EPTSTA_RX_SETUP ; 
 struct avr32dci_softc* AVR32_PC2SC (int /*<<< orphan*/ ) ; 
 int AVR32_READ_4 (struct avr32dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int,struct usb_page_search*) ; 

__attribute__((used)) static uint8_t
avr32dci_data_rx(struct avr32dci_td *td)
{
	struct avr32dci_softc *sc;
	struct usb_page_search buf_res;
	uint16_t count;
	uint32_t temp;
	uint8_t to;
	uint8_t got_short;

	to = 4;				/* don't loop forever! */
	got_short = 0;

	/* get pointer to softc */
	sc = AVR32_PC2SC(td->pc);

repeat:
	/* check if any of the FIFO banks have data */
	/* check endpoint status */
	temp = AVR32_READ_4(sc, AVR32_EPTSTA(td->ep_no));

	DPRINTFN(5, "EPTSTA(%u)=0x%08x\n", td->ep_no, temp);

	if (temp & AVR32_EPTSTA_RX_SETUP) {
		if (td->remainder == 0) {
			/*
			 * We are actually complete and have
			 * received the next SETUP
			 */
			DPRINTFN(5, "faking complete\n");
			return (0);	/* complete */
		}
		/*
	         * USB Host Aborted the transfer.
	         */
		td->error = 1;
		return (0);		/* complete */
	}
	/* check status */
	if (!(temp & AVR32_EPTSTA_RX_BK_RDY)) {
		/* no data */
		goto not_complete;
	}
	/* get the packet byte count */
	count = AVR32_EPTSTA_BYTE_COUNT(temp);

	/* verify the packet byte count */
	if (count != td->max_packet_size) {
		if (count < td->max_packet_size) {
			/* we have a short packet */
			td->short_pkt = 1;
			got_short = 1;
		} else {
			/* invalid USB packet */
			td->error = 1;
			return (0);	/* we are complete */
		}
	}
	/* verify the packet byte count */
	if (count > td->remainder) {
		/* invalid USB packet */
		td->error = 1;
		return (0);		/* we are complete */
	}
	while (count > 0) {
		usbd_get_page(td->pc, td->offset, &buf_res);

		/* get correct length */
		if (buf_res.length > count) {
			buf_res.length = count;
		}
		/* receive data */
		memcpy(buf_res.buffer, sc->physdata +
		    (AVR32_EPTSTA_CURRENT_BANK(temp) << td->bank_shift) +
		    (td->ep_no << 16) + (td->offset % td->max_packet_size), buf_res.length);
		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* clear OUT packet interrupt */
	AVR32_WRITE_4(sc, AVR32_EPTCLRSTA(td->ep_no), AVR32_EPTSTA_RX_BK_RDY);

	/* check if we are complete */
	if ((td->remainder == 0) || got_short) {
		if (td->short_pkt) {
			/* we are complete */
			return (0);
		}
		/* else need to receive a zero length packet */
	}
	if (--to) {
		goto repeat;
	}
not_complete:
	return (1);			/* not complete */
}
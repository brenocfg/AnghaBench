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
typedef  int uint16_t ;
struct usb_page_search {int length; int /*<<< orphan*/  buffer; } ;
struct atmegadci_td {int ep_no; int remainder; int error; int max_packet_size; int short_pkt; int offset; int /*<<< orphan*/  pc; } ;
struct atmegadci_softc {int dummy; } ;

/* Variables and functions */
 struct atmegadci_softc* ATMEGA_PC2SC (int /*<<< orphan*/ ) ; 
 int ATMEGA_READ_1 (struct atmegadci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATMEGA_READ_MULTI_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATMEGA_UEBCHX ; 
 int /*<<< orphan*/  ATMEGA_UEBCLX ; 
 int /*<<< orphan*/  ATMEGA_UEDATX ; 
 int /*<<< orphan*/  ATMEGA_UEIENX ; 
 int ATMEGA_UEIENX_RXOUTE ; 
 int ATMEGA_UEIENX_RXSTPE ; 
 int /*<<< orphan*/  ATMEGA_UEINTX ; 
 int ATMEGA_UEINTX_FIFOCON ; 
 int ATMEGA_UEINTX_RXOUTI ; 
 int ATMEGA_UEINTX_RXSTPI ; 
 int /*<<< orphan*/  ATMEGA_UENUM ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int,struct usb_page_search*) ; 

__attribute__((used)) static uint8_t
atmegadci_data_rx(struct atmegadci_td *td)
{
	struct atmegadci_softc *sc;
	struct usb_page_search buf_res;
	uint16_t count;
	uint8_t temp;
	uint8_t to;
	uint8_t got_short;

	to = 3;				/* don't loop forever! */
	got_short = 0;

	/* get pointer to softc */
	sc = ATMEGA_PC2SC(td->pc);

	/* select endpoint number */
	ATMEGA_WRITE_1(sc, ATMEGA_UENUM, td->ep_no);

repeat:
	/* check if any of the FIFO banks have data */
	/* check endpoint status */
	temp = ATMEGA_READ_1(sc, ATMEGA_UEINTX);

	DPRINTFN(5, "temp=0x%02x rem=%u\n", temp, td->remainder);

	if (temp & ATMEGA_UEINTX_RXSTPI) {
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
	if (!(temp & (ATMEGA_UEINTX_FIFOCON |
	    ATMEGA_UEINTX_RXOUTI))) {
		/* no data */
		goto not_complete;
	}
	/* get the packet byte count */
	count =
	    (ATMEGA_READ_1(sc, ATMEGA_UEBCHX) << 8) |
	    (ATMEGA_READ_1(sc, ATMEGA_UEBCLX));

	/* mask away undefined bits */
	count &= 0x7FF;

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
		ATMEGA_READ_MULTI_1(sc, ATMEGA_UEDATX,
		    buf_res.buffer, buf_res.length);

		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* clear OUT packet interrupt */
	ATMEGA_WRITE_1(sc, ATMEGA_UEINTX, ATMEGA_UEINTX_RXOUTI ^ 0xFF);

	/* release FIFO bank */
	ATMEGA_WRITE_1(sc, ATMEGA_UEINTX, ATMEGA_UEINTX_FIFOCON ^ 0xFF);

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
	/* we only want to know if there is a SETUP packet or OUT packet */
	ATMEGA_WRITE_1(sc, ATMEGA_UEIENX,
	    ATMEGA_UEIENX_RXSTPE | ATMEGA_UEIENX_RXOUTE);
	return (1);			/* not complete */
}
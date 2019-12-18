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
typedef  scalar_t__ uint16_t ;
struct usb_page_search {scalar_t__ length; int /*<<< orphan*/  buffer; } ;
struct atmegadci_td {int ep_no; scalar_t__ remainder; int error; scalar_t__ max_packet_size; int short_pkt; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; } ;
struct atmegadci_softc {int dummy; } ;

/* Variables and functions */
 struct atmegadci_softc* ATMEGA_PC2SC (int /*<<< orphan*/ ) ; 
 int ATMEGA_READ_1 (struct atmegadci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATMEGA_UEDATX ; 
 int /*<<< orphan*/  ATMEGA_UEIENX ; 
 int ATMEGA_UEIENX_RXSTPE ; 
 int ATMEGA_UEIENX_TXINE ; 
 int /*<<< orphan*/  ATMEGA_UEINTX ; 
 int ATMEGA_UEINTX_FIFOCON ; 
 int ATMEGA_UEINTX_RXSTPI ; 
 int ATMEGA_UEINTX_TXINI ; 
 int /*<<< orphan*/  ATMEGA_UENUM ; 
 int /*<<< orphan*/  ATMEGA_UESTA0X ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATMEGA_WRITE_MULTI_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_page_search*) ; 

__attribute__((used)) static uint8_t
atmegadci_data_tx(struct atmegadci_td *td)
{
	struct atmegadci_softc *sc;
	struct usb_page_search buf_res;
	uint16_t count;
	uint8_t to;
	uint8_t temp;

	to = 3;				/* don't loop forever! */

	/* get pointer to softc */
	sc = ATMEGA_PC2SC(td->pc);

	/* select endpoint number */
	ATMEGA_WRITE_1(sc, ATMEGA_UENUM, td->ep_no);

repeat:

	/* check endpoint status */
	temp = ATMEGA_READ_1(sc, ATMEGA_UEINTX);

	DPRINTFN(5, "temp=0x%02x rem=%u\n", temp, td->remainder);

	if (temp & ATMEGA_UEINTX_RXSTPI) {
		/*
	         * The current transfer was aborted
	         * by the USB Host
	         */
		td->error = 1;
		return (0);		/* complete */
	}

	temp = ATMEGA_READ_1(sc, ATMEGA_UESTA0X);
	if (temp & 3) {
		/* cannot write any data - a bank is busy */
		goto not_complete;
	}

	count = td->max_packet_size;
	if (td->remainder < count) {
		/* we have a short packet */
		td->short_pkt = 1;
		count = td->remainder;
	}
	while (count > 0) {

		usbd_get_page(td->pc, td->offset, &buf_res);

		/* get correct length */
		if (buf_res.length > count) {
			buf_res.length = count;
		}
		/* transmit data */
		ATMEGA_WRITE_MULTI_1(sc, ATMEGA_UEDATX,
		    buf_res.buffer, buf_res.length);

		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* clear IN packet interrupt */
	ATMEGA_WRITE_1(sc, ATMEGA_UEINTX, 0xFF ^ ATMEGA_UEINTX_TXINI);

	/* allocate FIFO bank */
	ATMEGA_WRITE_1(sc, ATMEGA_UEINTX, 0xFF ^ ATMEGA_UEINTX_FIFOCON);

	/* check remainder */
	if (td->remainder == 0) {
		if (td->short_pkt) {
			return (0);	/* complete */
		}
		/* else we need to transmit a short packet */
	}
	if (--to) {
		goto repeat;
	}
not_complete:
	/* we only want to know if there is a SETUP packet or free IN packet */
	ATMEGA_WRITE_1(sc, ATMEGA_UEIENX,
	    ATMEGA_UEIENX_RXSTPE | ATMEGA_UEIENX_TXINE);
	return (1);			/* not complete */
}
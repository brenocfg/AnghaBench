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
struct uss820dci_td {int ep_index; int remainder; int error; int did_enable; int max_packet_size; int short_pkt; int offset; int /*<<< orphan*/  pc; } ;
struct uss820dci_softc {int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;
struct usb_page_search {int length; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  USS820_DCI_PC2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USS820_EPCON ; 
 int /*<<< orphan*/  USS820_EPCON_RXIE ; 
 int /*<<< orphan*/  USS820_EPINDEX ; 
 int USS820_READ_1 (struct uss820dci_softc*,int /*<<< orphan*/ ) ; 
 int USS820_REG_STRIDE ; 
 int /*<<< orphan*/  USS820_RXCNTH ; 
 int /*<<< orphan*/  USS820_RXCNTL ; 
 int /*<<< orphan*/  USS820_RXCON ; 
 int USS820_RXCON_RXFFRC ; 
 int USS820_RXDAT ; 
 int /*<<< orphan*/  USS820_RXFLG ; 
 int USS820_RXFLG_RXFIF0 ; 
 int USS820_RXFLG_RXFIF1 ; 
 int USS820_RXFLG_RXOVF ; 
 int USS820_RXFLG_RXURF ; 
 int /*<<< orphan*/  USS820_RXSTAT ; 
 int USS820_RXSTAT_EDOVW ; 
 int USS820_RXSTAT_RXSETUP ; 
 int USS820_RXSTAT_RXSOVW ; 
 int /*<<< orphan*/  USS820_WRITE_1 (struct uss820dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_read_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int,struct usb_page_search*) ; 
 int /*<<< orphan*/  uss820dci_update_shared_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
uss820dci_data_rx(struct uss820dci_softc *sc, struct uss820dci_td *td)
{
	struct usb_page_search buf_res;
	uint16_t count;
	uint8_t rx_flag;
	uint8_t rx_stat;
	uint8_t rx_cntl;
	uint8_t to;
	uint8_t got_short;

	to = 2;				/* don't loop forever! */
	got_short = 0;

	/* select the correct endpoint */
	USS820_WRITE_1(sc, USS820_EPINDEX, td->ep_index);

	/* check if any of the FIFO banks have data */
repeat:
	/* read out FIFO flag */
	rx_flag = USS820_READ_1(sc, USS820_RXFLG);
	/* read out FIFO status */
	rx_stat = USS820_READ_1(sc, USS820_RXSTAT);

	DPRINTFN(5, "rx_stat=0x%02x rx_flag=0x%02x rem=%u\n",
	    rx_stat, rx_flag, td->remainder);

	if (rx_stat & (USS820_RXSTAT_RXSETUP |
	    USS820_RXSTAT_RXSOVW |
	    USS820_RXSTAT_EDOVW)) {
		if (td->remainder == 0 && td->ep_index == 0) {
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
	/* check for errors */
	if (rx_flag & (USS820_RXFLG_RXOVF |
	    USS820_RXFLG_RXURF)) {
		DPRINTFN(5, "overflow or underflow\n");
		/* should not happen */
		td->error = 1;
		return (0);		/* complete */
	}
	/* check status */
	if (!(rx_flag & (USS820_RXFLG_RXFIF0 |
	    USS820_RXFLG_RXFIF1))) {

		/* read out EPCON register */
		/* enable RX input */
		if (!td->did_enable) {
			uss820dci_update_shared_1(USS820_DCI_PC2SC(td->pc),
			    USS820_EPCON, 0xFF, USS820_EPCON_RXIE);
			td->did_enable = 1;
		}
		return (1);		/* not complete */
	}
	/* get the packet byte count */
	count = USS820_READ_1(sc, USS820_RXCNTL);
	count |= (USS820_READ_1(sc, USS820_RXCNTH) << 8);
	count &= 0x3FF;

	DPRINTFN(5, "count=0x%04x\n", count);

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
		bus_space_read_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
		    USS820_RXDAT * USS820_REG_STRIDE, buf_res.buffer, buf_res.length);

		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* set RXFFRC bit */
	rx_cntl = USS820_READ_1(sc, USS820_RXCON);
	rx_cntl |= USS820_RXCON_RXFFRC;
	USS820_WRITE_1(sc, USS820_RXCON, rx_cntl);

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
	return (1);			/* not complete */
}
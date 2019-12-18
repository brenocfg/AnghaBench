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
struct uss820dci_td {scalar_t__ ep_index; scalar_t__ remainder; int error; scalar_t__ max_packet_size; int short_pkt; int did_enable; int /*<<< orphan*/  pc; int /*<<< orphan*/  offset; int /*<<< orphan*/  support_multi_buffer; } ;
struct uss820dci_softc {int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;
struct usb_page_search {scalar_t__ length; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,...) ; 
 int /*<<< orphan*/  USS820_DCI_PC2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USS820_EPCON ; 
 int /*<<< orphan*/  USS820_EPCON_TXOE ; 
 int /*<<< orphan*/  USS820_EPINDEX ; 
 int USS820_READ_1 (struct uss820dci_softc*,int /*<<< orphan*/ ) ; 
 int USS820_REG_STRIDE ; 
 int /*<<< orphan*/  USS820_RXSTAT ; 
 int USS820_RXSTAT_EDOVW ; 
 int USS820_RXSTAT_RXSETUP ; 
 int USS820_RXSTAT_RXSOVW ; 
 int /*<<< orphan*/  USS820_TXCNTH ; 
 int /*<<< orphan*/  USS820_TXCNTL ; 
 int USS820_TXDAT ; 
 int /*<<< orphan*/  USS820_TXFLG ; 
 int USS820_TXFLG_TXFIF0 ; 
 int USS820_TXFLG_TXFIF1 ; 
 int USS820_TXFLG_TXOVF ; 
 int USS820_TXFLG_TXURF ; 
 int /*<<< orphan*/  USS820_WRITE_1 (struct uss820dci_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_write_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  uss820dci_update_shared_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
uss820dci_data_tx(struct uss820dci_softc *sc, struct uss820dci_td *td)
{
	struct usb_page_search buf_res;
	uint16_t count;
	uint16_t count_copy;
	uint8_t rx_stat;
	uint8_t tx_flag;
	uint8_t to;

	/* select the correct endpoint */
	USS820_WRITE_1(sc, USS820_EPINDEX, td->ep_index);

	to = 2;				/* don't loop forever! */

repeat:
	/* read out TX FIFO flags */
	tx_flag = USS820_READ_1(sc, USS820_TXFLG);

	DPRINTFN(5, "tx_flag=0x%02x rem=%u\n", tx_flag, td->remainder);

	if (td->ep_index == 0) {
		/* read out RX FIFO status last */
		rx_stat = USS820_READ_1(sc, USS820_RXSTAT);

		DPRINTFN(5, "rx_stat=0x%02x\n", rx_stat);

		if (rx_stat & (USS820_RXSTAT_RXSETUP |
		    USS820_RXSTAT_RXSOVW |
		    USS820_RXSTAT_EDOVW)) {
			/*
			 * The current transfer was aborted by the USB
			 * Host:
			 */
			td->error = 1;
			return (0);		/* complete */
		}
	}
	if (tx_flag & (USS820_TXFLG_TXOVF |
	    USS820_TXFLG_TXURF)) {
		td->error = 1;
		return (0);		/* complete */
	}
	if (tx_flag & USS820_TXFLG_TXFIF0) {
		if (tx_flag & USS820_TXFLG_TXFIF1) {
			return (1);	/* not complete */
		}
	}
	if ((!td->support_multi_buffer) &&
	    (tx_flag & (USS820_TXFLG_TXFIF0 |
	    USS820_TXFLG_TXFIF1))) {
		return (1);		/* not complete */
	}
	count = td->max_packet_size;
	if (td->remainder < count) {
		/* we have a short packet */
		td->short_pkt = 1;
		count = td->remainder;
	}
	count_copy = count;
	while (count > 0) {

		usbd_get_page(td->pc, td->offset, &buf_res);

		/* get correct length */
		if (buf_res.length > count) {
			buf_res.length = count;
		}
		/* transmit data */
		bus_space_write_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
		    USS820_TXDAT * USS820_REG_STRIDE, buf_res.buffer, buf_res.length);

		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* post-write high packet byte count first */
	USS820_WRITE_1(sc, USS820_TXCNTH, count_copy >> 8);

	/* post-write low packet byte count last */
	USS820_WRITE_1(sc, USS820_TXCNTL, count_copy);

	/*
	 * Enable TX output, which must happen after that we have written
	 * data into the FIFO. This is undocumented.
	 */
	if (!td->did_enable) {
		uss820dci_update_shared_1(USS820_DCI_PC2SC(td->pc),
		    USS820_EPCON, 0xFF, USS820_EPCON_TXOE);
		td->did_enable = 1;
	}
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
	return (1);			/* not complete */
}
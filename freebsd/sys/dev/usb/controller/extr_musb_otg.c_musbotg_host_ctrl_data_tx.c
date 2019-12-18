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
typedef  int uint16_t ;
struct usb_page_search {int length; void* buffer; } ;
struct musbotg_td {int channel; int error; int transaction_started; scalar_t__ remainder; int short_pkt; int max_frame_size; int offset; int dev_addr; int haddr; int hport; int transfer_type; int /*<<< orphan*/  pc; } ;
struct musbotg_softc {void* sc_bounce_buf; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int MAX_NAK_TO ; 
 int MUSB2_MASK_CSR0H_FFLUSH ; 
 int MUSB2_MASK_CSR0L_ERROR ; 
 int MUSB2_MASK_CSR0L_NAKTIMO ; 
 int MUSB2_MASK_CSR0L_RXSTALL ; 
 int MUSB2_MASK_CSR0L_TXFIFONEMPTY ; 
 int MUSB2_MASK_CSR0L_TXPKTRDY ; 
 int MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRH ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRL ; 
 int /*<<< orphan*/  MUSB2_REG_TXFADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_TXHADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_TXHUBPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_TXNAKLIMIT ; 
 int /*<<< orphan*/  MUSB2_REG_TXTI ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
 struct musbotg_softc* MUSBOTG_PC2SC (int /*<<< orphan*/ ) ; 
 int USB_P2U (void*) ; 
 int /*<<< orphan*/  bus_space_write_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  bus_space_write_multi_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int musbotg_channel_alloc (struct musbotg_softc*,struct musbotg_td*,int) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 
 int /*<<< orphan*/  usbd_copy_out (int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int,struct usb_page_search*) ; 

__attribute__((used)) static uint8_t
musbotg_host_ctrl_data_tx(struct musbotg_td *td)
{
	struct usb_page_search buf_res;
	struct musbotg_softc *sc;
	uint16_t count;
	uint8_t csr, csrh;

	/* get pointer to softc */
	sc = MUSBOTG_PC2SC(td->pc);

	if (td->channel == -1)
		td->channel = musbotg_channel_alloc(sc, td, 1);

	/* No free EPs */
	if (td->channel == -1)
		return (1);

	DPRINTFN(1, "ep_no=%d\n", td->channel);

	/* select endpoint */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, 0);

	/* read out FIFO status */
	csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
	DPRINTFN(4, "csr=0x%02x\n", csr);

	if (csr & (MUSB2_MASK_CSR0L_RXSTALL |
	    MUSB2_MASK_CSR0L_ERROR)) {
		/* clear status bits */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, 0);
		td->error = 1;
	}

	if (csr & MUSB2_MASK_CSR0L_NAKTIMO ) {

		if (csr & MUSB2_MASK_CSR0L_TXFIFONEMPTY) {
			csrh = MUSB2_READ_1(sc, MUSB2_REG_TXCSRH);
			csrh |= MUSB2_MASK_CSR0H_FFLUSH;
			MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRH, csrh);
			csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
			if (csr & MUSB2_MASK_CSR0L_TXFIFONEMPTY) {
				csrh = MUSB2_READ_1(sc, MUSB2_REG_TXCSRH);
				csrh |= MUSB2_MASK_CSR0H_FFLUSH;
				MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRH, csrh);
				csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
			}
		}

		csr &= ~MUSB2_MASK_CSR0L_NAKTIMO;
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, csr);

		td->error = 1;
	}


	if (td->error) {
		musbotg_channel_free(sc, td);
		return (0);	/* complete */
	}

	/*
	 * Wait while FIFO is empty. 
	 * Do not flush it because it will cause transactions
	 * with size more then packet size. It might upset
	 * some devices
	 */
	if (csr & MUSB2_MASK_CSR0L_TXFIFONEMPTY)
		return (1);

	/* Packet still being processed */
	if (csr & MUSB2_MASK_CSR0L_TXPKTRDY)
		return (1);

	if (td->transaction_started) {
		/* check remainder */
		if (td->remainder == 0) {
			if (td->short_pkt) {
				musbotg_channel_free(sc, td);
				return (0);	/* complete */
			}
			/* else we need to transmit a short packet */
		}

		/* We're not complete - more transactions required */
		td->transaction_started = 0;
	}

	/* check for short packet */
	count = td->max_frame_size;
	if (td->remainder < count) {
		/* we have a short packet */
		td->short_pkt = 1;
		count = td->remainder;
	}

	while (count > 0) {
		uint32_t temp;

		usbd_get_page(td->pc, td->offset, &buf_res);

		/* get correct length */
		if (buf_res.length > count) {
			buf_res.length = count;
		}
		/* check for unaligned memory address */
		if (USB_P2U(buf_res.buffer) & 3) {

			usbd_copy_out(td->pc, td->offset,
			    sc->sc_bounce_buf, count);

			temp = count & ~3;

			if (temp) {
				/* transmit data 4 bytes at a time */
				bus_space_write_multi_4(sc->sc_io_tag,
				    sc->sc_io_hdl, MUSB2_REG_EPFIFO(0),
				    sc->sc_bounce_buf, temp / 4);
			}
			temp = count & 3;
			if (temp) {
				/* receive data 1 byte at a time */
				bus_space_write_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
				    MUSB2_REG_EPFIFO(0),
				    ((void *)&sc->sc_bounce_buf[count / 4]), temp);
			}
			/* update offset and remainder */
			td->offset += count;
			td->remainder -= count;
			break;
		}
		/* check if we can optimise */
		if (buf_res.length >= 4) {

			/* transmit data 4 bytes at a time */
			bus_space_write_multi_4(sc->sc_io_tag, sc->sc_io_hdl,
			    MUSB2_REG_EPFIFO(0), buf_res.buffer,
			    buf_res.length / 4);

			temp = buf_res.length & ~3;

			/* update counters */
			count -= temp;
			td->offset += temp;
			td->remainder -= temp;
			continue;
		}
		/* transmit data */
		bus_space_write_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
		    MUSB2_REG_EPFIFO(0), buf_res.buffer,
		    buf_res.length);

		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* Function address */
	MUSB2_WRITE_1(sc, MUSB2_REG_TXFADDR(0), td->dev_addr);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXHADDR(0), td->haddr);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXHUBPORT(0), td->hport);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXTI, td->transfer_type);

	/* TX NAK timeout */
	MUSB2_WRITE_1(sc, MUSB2_REG_TXNAKLIMIT, MAX_NAK_TO);

	/* write command */
	MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
	    MUSB2_MASK_CSR0L_TXPKTRDY);

	td->transaction_started = 1;

	return (1);			/* not complete */
}
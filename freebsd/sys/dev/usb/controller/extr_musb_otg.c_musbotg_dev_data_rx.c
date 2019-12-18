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
struct musbotg_td {int channel; int max_frame_size; int short_pkt; int error; int remainder; int offset; int /*<<< orphan*/  pc; } ;
struct musbotg_softc {void* sc_bounce_buf; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int MUSB2_MASK_CSRL_RXOVERRUN ; 
 int MUSB2_MASK_CSRL_RXPKTRDY ; 
 int MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int MUSB2_READ_2 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPFIFO (int) ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_RXCOUNT ; 
 int /*<<< orphan*/  MUSB2_REG_RXCSRL ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
 struct musbotg_softc* MUSBOTG_PC2SC (int /*<<< orphan*/ ) ; 
 int USB_P2U (void*) ; 
 int /*<<< orphan*/  bus_space_read_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  bus_space_read_multi_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int musbotg_channel_alloc (struct musbotg_softc*,struct musbotg_td*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 
 int /*<<< orphan*/  usbd_copy_in (int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ ,int,struct usb_page_search*) ; 

__attribute__((used)) static uint8_t
musbotg_dev_data_rx(struct musbotg_td *td)
{
	struct usb_page_search buf_res;
	struct musbotg_softc *sc;
	uint16_t count;
	uint8_t csr;
	uint8_t to;
	uint8_t got_short;

	to = 8;				/* don't loop forever! */
	got_short = 0;

	/* get pointer to softc */
	sc = MUSBOTG_PC2SC(td->pc);

	if (td->channel == -1)
		td->channel = musbotg_channel_alloc(sc, td, 0);

	/* EP0 is busy, wait */
	if (td->channel == -1)
		return (1);

	/* select endpoint */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, td->channel);

repeat:
	/* read out FIFO status */
	csr = MUSB2_READ_1(sc, MUSB2_REG_RXCSRL);

	DPRINTFN(4, "csr=0x%02x\n", csr);

	/* clear overrun */
	if (csr & MUSB2_MASK_CSRL_RXOVERRUN) {
		/* make sure we don't clear "RXPKTRDY" */
		MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL,
		    MUSB2_MASK_CSRL_RXPKTRDY);
	}

	/* check status */
	if (!(csr & MUSB2_MASK_CSRL_RXPKTRDY))
		return (1); /* not complete */

	/* get the packet byte count */
	count = MUSB2_READ_2(sc, MUSB2_REG_RXCOUNT);

	DPRINTFN(4, "count=0x%04x\n", count);

	/*
	 * Check for short or invalid packet:
	 */
	if (count != td->max_frame_size) {
		if (count < td->max_frame_size) {
			/* we have a short packet */
			td->short_pkt = 1;
			got_short = 1;
		} else {
			/* invalid USB packet */
			td->error = 1;
			musbotg_channel_free(sc, td);
			return (0);	/* we are complete */
		}
	}
	/* verify the packet byte count */
	if (count > td->remainder) {
		/* invalid USB packet */
		td->error = 1;
		musbotg_channel_free(sc, td);
		return (0);		/* we are complete */
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

			temp = count & ~3;

			if (temp) {
				/* receive data 4 bytes at a time */
				bus_space_read_multi_4(sc->sc_io_tag, sc->sc_io_hdl,
				    MUSB2_REG_EPFIFO(td->channel), sc->sc_bounce_buf,
				    temp / 4);
			}
			temp = count & 3;
			if (temp) {
				/* receive data 1 byte at a time */
				bus_space_read_multi_1(sc->sc_io_tag,
				    sc->sc_io_hdl, MUSB2_REG_EPFIFO(td->channel),
				    ((void *)&sc->sc_bounce_buf[count / 4]), temp);
			}
			usbd_copy_in(td->pc, td->offset,
			    sc->sc_bounce_buf, count);

			/* update offset and remainder */
			td->offset += count;
			td->remainder -= count;
			break;
		}
		/* check if we can optimise */
		if (buf_res.length >= 4) {

			/* receive data 4 bytes at a time */
			bus_space_read_multi_4(sc->sc_io_tag, sc->sc_io_hdl,
			    MUSB2_REG_EPFIFO(td->channel), buf_res.buffer,
			    buf_res.length / 4);

			temp = buf_res.length & ~3;

			/* update counters */
			count -= temp;
			td->offset += temp;
			td->remainder -= temp;
			continue;
		}
		/* receive data */
		bus_space_read_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
		    MUSB2_REG_EPFIFO(td->channel), buf_res.buffer,
		    buf_res.length);

		/* update counters */
		count -= buf_res.length;
		td->offset += buf_res.length;
		td->remainder -= buf_res.length;
	}

	/* clear status bits */
	MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL, 0);

	/* check if we are complete */
	if ((td->remainder == 0) || got_short) {
		if (td->short_pkt) {
			/* we are complete */
			musbotg_channel_free(sc, td);
			return (0);
		}
		/* else need to receive a zero length packet */
	}
	if (--to) {
		goto repeat;
	}
	return (1);			/* not complete */
}
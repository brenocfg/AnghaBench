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
struct usb_device_request {scalar_t__ bmRequestType; scalar_t__ bRequest; int* wValue; } ;
struct musbotg_td {int channel; int did_stall; int remainder; int offset; int /*<<< orphan*/  pc; } ;
struct musbotg_softc {int sc_ep0_busy; int sc_dv_addr; scalar_t__ sc_ep0_cmd; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int MUSB2_MASK_CSR0L_DATAEND ; 
 int MUSB2_MASK_CSR0L_RXPKTRDY ; 
 scalar_t__ MUSB2_MASK_CSR0L_RXPKTRDY_CLR ; 
 scalar_t__ MUSB2_MASK_CSR0L_SENDSTALL ; 
 int MUSB2_MASK_CSR0L_SENTSTALL ; 
 int MUSB2_MASK_CSR0L_SETUPEND ; 
 scalar_t__ MUSB2_MASK_CSR0L_SETUPEND_CLR ; 
 int MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int MUSB2_READ_2 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_RXCOUNT ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRL ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct musbotg_softc* MUSBOTG_PC2SC (int /*<<< orphan*/ ) ; 
 scalar_t__ UR_SET_ADDRESS ; 
 scalar_t__ UT_WRITE_DEVICE ; 
 int /*<<< orphan*/  bus_space_read_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int musbotg_channel_alloc (struct musbotg_softc*,struct musbotg_td*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 
 int /*<<< orphan*/  usbd_copy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 

__attribute__((used)) static uint8_t
musbotg_dev_ctrl_setup_rx(struct musbotg_td *td)
{
	struct musbotg_softc *sc;
	struct usb_device_request req;
	uint16_t count;
	uint8_t csr;

	/* get pointer to softc */
	sc = MUSBOTG_PC2SC(td->pc);

	if (td->channel == -1)
		td->channel = musbotg_channel_alloc(sc, td, 0);

	/* EP0 is busy, wait */
	if (td->channel == -1)
		return (1);

	DPRINTFN(1, "ep_no=%d\n", td->channel);

	/* select endpoint 0 */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, 0);

	/* read out FIFO status */
	csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);

	DPRINTFN(4, "csr=0x%02x\n", csr);

	/*
	 * NOTE: If DATAEND is set we should not call the
	 * callback, hence the status stage is not complete.
	 */
	if (csr & MUSB2_MASK_CSR0L_DATAEND) {
		/* do not stall at this point */
		td->did_stall = 1;
		/* wait for interrupt */
		DPRINTFN(1, "CSR0 DATAEND\n");
		goto not_complete;
	}

	if (csr & MUSB2_MASK_CSR0L_SENTSTALL) {
		/* clear SENTSTALL */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, 0);
		/* get latest status */
		csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
		/* update EP0 state */
		sc->sc_ep0_busy = 0;
	}
	if (csr & MUSB2_MASK_CSR0L_SETUPEND) {
		/* clear SETUPEND */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		    MUSB2_MASK_CSR0L_SETUPEND_CLR);
		/* get latest status */
		csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
		/* update EP0 state */
		sc->sc_ep0_busy = 0;
	}
	if (sc->sc_ep0_busy) {
		DPRINTFN(1, "EP0 BUSY\n");
		goto not_complete;
	}
	if (!(csr & MUSB2_MASK_CSR0L_RXPKTRDY)) {
		goto not_complete;
	}
	/* get the packet byte count */
	count = MUSB2_READ_2(sc, MUSB2_REG_RXCOUNT);

	/* verify data length */
	if (count != td->remainder) {
		DPRINTFN(1, "Invalid SETUP packet "
		    "length, %d bytes\n", count);
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		      MUSB2_MASK_CSR0L_RXPKTRDY_CLR);
		/* don't clear stall */
		td->did_stall = 1;
		goto not_complete;
	}
	if (count != sizeof(req)) {
		DPRINTFN(1, "Unsupported SETUP packet "
		    "length, %d bytes\n", count);
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		      MUSB2_MASK_CSR0L_RXPKTRDY_CLR);
		/* don't clear stall */
		td->did_stall = 1;
		goto not_complete;
	}
	/* clear did stall flag */
	td->did_stall = 0;

	/* receive data */
	bus_space_read_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
	    MUSB2_REG_EPFIFO(0), (void *)&req, sizeof(req));

	/* copy data into real buffer */
	usbd_copy_in(td->pc, 0, &req, sizeof(req));

	td->offset = sizeof(req);
	td->remainder = 0;

	/* set pending command */
	sc->sc_ep0_cmd = MUSB2_MASK_CSR0L_RXPKTRDY_CLR;

	/* we need set stall or dataend after this */
	sc->sc_ep0_busy = 1;

	/* sneak peek the set address */
	if ((req.bmRequestType == UT_WRITE_DEVICE) &&
	    (req.bRequest == UR_SET_ADDRESS)) {
		sc->sc_dv_addr = req.wValue[0] & 0x7F;
	} else {
		sc->sc_dv_addr = 0xFF;
	}

	musbotg_channel_free(sc, td);
	return (0);			/* complete */

not_complete:
	/* abort any ongoing transfer */
	if (!td->did_stall) {
		DPRINTFN(4, "stalling\n");
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		    MUSB2_MASK_CSR0L_SENDSTALL);
		td->did_stall = 1;
	}
	return (1);			/* not complete */
}
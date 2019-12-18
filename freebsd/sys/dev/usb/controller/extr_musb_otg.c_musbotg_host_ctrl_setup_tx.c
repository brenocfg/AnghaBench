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
struct usb_device_request {int dummy; } ;
struct musbotg_td {int channel; int error; scalar_t__ remainder; int offset; int dev_addr; int haddr; int hport; int transfer_type; int transaction_started; int /*<<< orphan*/  pc; } ;
struct musbotg_softc {int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int MAX_NAK_TO ; 
 int MUSB2_MASK_CSR0H_FFLUSH ; 
 int MUSB2_MASK_CSR0L_ERROR ; 
 int MUSB2_MASK_CSR0L_NAKTIMO ; 
 int MUSB2_MASK_CSR0L_RXSTALL ; 
 int MUSB2_MASK_CSR0L_SETUPPKT ; 
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
 int /*<<< orphan*/  bus_space_write_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int musbotg_channel_alloc (struct musbotg_softc*,struct musbotg_td*,int) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 
 int /*<<< orphan*/  usbd_copy_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 

__attribute__((used)) static uint8_t
musbotg_host_ctrl_setup_tx(struct musbotg_td *td)
{
	struct musbotg_softc *sc;
	struct usb_device_request req;
	uint8_t csr, csrh;

	/* get pointer to softc */
	sc = MUSBOTG_PC2SC(td->pc);

	if (td->channel == -1)
		td->channel = musbotg_channel_alloc(sc, td, 1);

	/* EP0 is busy, wait */
	if (td->channel == -1)
		return (1);

	DPRINTFN(1, "ep_no=%d\n", td->channel);

	/* select endpoint 0 */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, 0);

	/* read out FIFO status */
	csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
	DPRINTFN(4, "csr=0x%02x\n", csr);

	/* Not ready yet yet */
	if (csr & MUSB2_MASK_CSR0L_TXPKTRDY)
		return (1);

	/* Failed */
	if (csr & (MUSB2_MASK_CSR0L_RXSTALL |
	    MUSB2_MASK_CSR0L_ERROR))
	{
		/* Clear status bit */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, 0);
		DPRINTFN(1, "error bit set, csr=0x%02x\n", csr);
		td->error = 1;
	}

	if (csr & MUSB2_MASK_CSR0L_NAKTIMO) {
		DPRINTFN(1, "NAK timeout\n");

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
		return (0);
	}

	/* Fifo is not empty and there is no NAK timeout */
	if (csr & MUSB2_MASK_CSR0L_TXPKTRDY)
		return (1);

	/* check if we are complete */
	if (td->remainder == 0) {
		/* we are complete */
		musbotg_channel_free(sc, td);
		return (0);
	}

	/* copy data into real buffer */
	usbd_copy_out(td->pc, 0, &req, sizeof(req));

	/* send data */
	bus_space_write_multi_1(sc->sc_io_tag, sc->sc_io_hdl,
	    MUSB2_REG_EPFIFO(0), (void *)&req, sizeof(req));

	/* update offset and remainder */
	td->offset += sizeof(req);
	td->remainder -= sizeof(req);


	MUSB2_WRITE_1(sc, MUSB2_REG_TXNAKLIMIT, MAX_NAK_TO);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXFADDR(0), td->dev_addr);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXHADDR(0), td->haddr);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXHUBPORT(0), td->hport);
	MUSB2_WRITE_1(sc, MUSB2_REG_TXTI, td->transfer_type);

	/* write command */
	MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
	    MUSB2_MASK_CSR0L_TXPKTRDY | 
	    MUSB2_MASK_CSR0L_SETUPPKT);

	/* Just to be consistent, not used above */
	td->transaction_started = 1;

	return (1);			/* in progress */
}
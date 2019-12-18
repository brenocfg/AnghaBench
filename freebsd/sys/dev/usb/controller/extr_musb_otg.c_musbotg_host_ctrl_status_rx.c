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
struct musbotg_td {int channel; int transaction_started; int dev_addr; int haddr; int hport; int transfer_type; int error; int /*<<< orphan*/  pc; } ;
struct musbotg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int MAX_NAK_TO ; 
 int MUSB2_MASK_CSR0H_PING_DIS ; 
 int MUSB2_MASK_CSR0L_ERROR ; 
 int MUSB2_MASK_CSR0L_NAKTIMO ; 
 int MUSB2_MASK_CSR0L_REQPKT ; 
 int MUSB2_MASK_CSR0L_RXPKTRDY ; 
 int MUSB2_MASK_CSR0L_RXPKTRDY_CLR ; 
 int MUSB2_MASK_CSR0L_RXSTALL ; 
 int MUSB2_MASK_CSR0L_STATUSPKT ; 
 int MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_RXCSRH ; 
 int /*<<< orphan*/  MUSB2_REG_RXFADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_RXHADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_RXHUBPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_RXNAKLIMIT ; 
 int /*<<< orphan*/  MUSB2_REG_RXTI ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRL ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
 struct musbotg_softc* MUSBOTG_PC2SC (int /*<<< orphan*/ ) ; 
 int musbotg_channel_alloc (struct musbotg_softc*,struct musbotg_td*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 

__attribute__((used)) static uint8_t
musbotg_host_ctrl_status_rx(struct musbotg_td *td)
{
	struct musbotg_softc *sc;
	uint8_t csr, csrh;

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

	if (!td->transaction_started) {
		MUSB2_WRITE_1(sc, MUSB2_REG_RXFADDR(0),
		    td->dev_addr);

		MUSB2_WRITE_1(sc, MUSB2_REG_RXHADDR(0), td->haddr);
		MUSB2_WRITE_1(sc, MUSB2_REG_RXHUBPORT(0), td->hport);
		MUSB2_WRITE_1(sc, MUSB2_REG_RXTI, td->transfer_type);

		/* RX NAK timeout */
		MUSB2_WRITE_1(sc, MUSB2_REG_RXNAKLIMIT, MAX_NAK_TO);

		td->transaction_started = 1;

		/* Disable PING */
		csrh = MUSB2_READ_1(sc, MUSB2_REG_RXCSRH);
		csrh |= MUSB2_MASK_CSR0H_PING_DIS;
		MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRH, csrh);

		/* write command */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		    MUSB2_MASK_CSR0L_STATUSPKT | 
		    MUSB2_MASK_CSR0L_REQPKT);

		return (1); /* Just started */

	}

	csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);

	DPRINTFN(4, "IN STATUS csr=0x%02x\n", csr);

	if (csr & MUSB2_MASK_CSR0L_RXPKTRDY) {
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		    MUSB2_MASK_CSR0L_RXPKTRDY_CLR);
		musbotg_channel_free(sc, td);
		return (0); /* complete */
	}

	if (csr & MUSB2_MASK_CSR0L_NAKTIMO) {
		csr &= ~ (MUSB2_MASK_CSR0L_STATUSPKT |
		    MUSB2_MASK_CSR0L_REQPKT);
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, csr);

		csr &= ~MUSB2_MASK_CSR0L_NAKTIMO;
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, csr);
		td->error = 1;
	}

	/* Failed */
	if (csr & (MUSB2_MASK_CSR0L_RXSTALL |
	    MUSB2_MASK_CSR0L_ERROR))
	{
		/* Clear status bit */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, 0);
		DPRINTFN(1, "error bit set, csr=0x%02x\n", csr);
		td->error = 1;
	}

	if (td->error) {
		musbotg_channel_free(sc, td);
		return (0);
	}

	return (1);			/* Not ready yet */
}
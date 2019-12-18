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
struct musbotg_td {int /*<<< orphan*/  pc; } ;
struct musbotg_softc {int sc_ep0_cmd; int sc_dv_addr; scalar_t__ sc_ep0_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int MUSB2_MASK_CSR0L_DATAEND ; 
 int MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRL ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
 struct musbotg_softc* MUSBOTG_PC2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 
 int /*<<< orphan*/  musbotg_set_address (struct musbotg_softc*,int) ; 

__attribute__((used)) static uint8_t
musbotg_dev_ctrl_status(struct musbotg_td *td)
{
	struct musbotg_softc *sc;
	uint8_t csr;

	/* get pointer to softc */
	sc = MUSBOTG_PC2SC(td->pc);

	/* select endpoint 0 */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, 0);

	if (sc->sc_ep0_busy) {
		sc->sc_ep0_busy = 0;
		sc->sc_ep0_cmd |= MUSB2_MASK_CSR0L_DATAEND;
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, sc->sc_ep0_cmd);
		sc->sc_ep0_cmd = 0;
	}
	/* read out FIFO status */
	csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);

	DPRINTFN(4, "csr=0x%02x\n", csr);

	if (csr & MUSB2_MASK_CSR0L_DATAEND) {
		/* wait for interrupt */
		return (1);		/* not complete */
	}
	if (sc->sc_dv_addr != 0xFF) {
		/* write function address */
		musbotg_set_address(sc, sc->sc_dv_addr);
	}

	musbotg_channel_free(sc, td);
	return (0);			/* complete */
}
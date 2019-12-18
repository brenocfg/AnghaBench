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
struct msk_softc {int dummy; } ;
struct msk_if_softc {int /*<<< orphan*/  msk_if_dev; int /*<<< orphan*/  msk_port; struct msk_softc* msk_softc; } ;

/* Variables and functions */
 int CSR_READ_1 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMAC_IRQ_SRC ; 
 int /*<<< orphan*/  GMF_CLI_RX_FO ; 
 int /*<<< orphan*/  GMF_CLI_TX_FU ; 
 int GM_IS_RX_FF_OR ; 
 int GM_IS_TX_FF_UR ; 
 int /*<<< orphan*/  MR_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
msk_intr_gmac(struct msk_if_softc *sc_if)
{
	struct msk_softc *sc;
	uint8_t status;

	sc = sc_if->msk_softc;
	status = CSR_READ_1(sc, MR_ADDR(sc_if->msk_port, GMAC_IRQ_SRC));

	/* GMAC Rx FIFO overrun. */
	if ((status & GM_IS_RX_FF_OR) != 0)
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T),
		    GMF_CLI_RX_FO);
	/* GMAC Tx FIFO underrun. */
	if ((status & GM_IS_TX_FF_UR) != 0) {
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_CTRL_T),
		    GMF_CLI_TX_FU);
		device_printf(sc_if->msk_if_dev, "Tx FIFO underrun!\n");
		/*
		 * XXX
		 * In case of Tx underrun, we may need to flush/reset
		 * Tx MAC but that would also require resynchronization
		 * with status LEs. Reinitializing status LEs would
		 * affect other port in dual MAC configuration so it
		 * should be avoided as possible as we can.
		 * Due to lack of documentation it's all vague guess but
		 * it needs more investigation.
		 */
	}
}
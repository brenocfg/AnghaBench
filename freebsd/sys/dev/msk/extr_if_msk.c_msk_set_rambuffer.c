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
struct msk_softc {int* msk_rxqstart; int* msk_rxqend; scalar_t__ msk_rxqsize; int* msk_txqstart; int* msk_txqend; } ;
struct msk_if_softc {int msk_flags; size_t msk_port; int /*<<< orphan*/  msk_txq; int /*<<< orphan*/  msk_rxq; struct msk_softc* msk_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int MSK_FLAG_RAMBUF ; 
 scalar_t__ MSK_MIN_RXQ_SIZE ; 
 int MSK_RB_LLPP_B ; 
 int MSK_RB_LLPP_S ; 
 int MSK_RB_ULPP ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int /*<<< orphan*/  RB_ENA_OP_MD ; 
 int /*<<< orphan*/  RB_ENA_STFWD ; 
 int /*<<< orphan*/  RB_END ; 
 int /*<<< orphan*/  RB_RP ; 
 int /*<<< orphan*/  RB_RST_CLR ; 
 int /*<<< orphan*/  RB_RX_LTPP ; 
 int /*<<< orphan*/  RB_RX_UTPP ; 
 int /*<<< orphan*/  RB_START ; 
 int /*<<< orphan*/  RB_WP ; 

__attribute__((used)) static void
msk_set_rambuffer(struct msk_if_softc *sc_if)
{
	struct msk_softc *sc;
	int ltpp, utpp;

	sc = sc_if->msk_softc;
	if ((sc_if->msk_flags & MSK_FLAG_RAMBUF) == 0)
		return;

	/* Setup Rx Queue. */
	CSR_WRITE_1(sc, RB_ADDR(sc_if->msk_rxq, RB_CTRL), RB_RST_CLR);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_rxq, RB_START),
	    sc->msk_rxqstart[sc_if->msk_port] / 8);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_rxq, RB_END),
	    sc->msk_rxqend[sc_if->msk_port] / 8);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_rxq, RB_WP),
	    sc->msk_rxqstart[sc_if->msk_port] / 8);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_rxq, RB_RP),
	    sc->msk_rxqstart[sc_if->msk_port] / 8);

	utpp = (sc->msk_rxqend[sc_if->msk_port] + 1 -
	    sc->msk_rxqstart[sc_if->msk_port] - MSK_RB_ULPP) / 8;
	ltpp = (sc->msk_rxqend[sc_if->msk_port] + 1 -
	    sc->msk_rxqstart[sc_if->msk_port] - MSK_RB_LLPP_B) / 8;
	if (sc->msk_rxqsize < MSK_MIN_RXQ_SIZE)
		ltpp += (MSK_RB_LLPP_B - MSK_RB_LLPP_S) / 8;
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_rxq, RB_RX_UTPP), utpp);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_rxq, RB_RX_LTPP), ltpp);
	/* Set Rx priority(RB_RX_UTHP/RB_RX_LTHP) thresholds? */

	CSR_WRITE_1(sc, RB_ADDR(sc_if->msk_rxq, RB_CTRL), RB_ENA_OP_MD);
	CSR_READ_1(sc, RB_ADDR(sc_if->msk_rxq, RB_CTRL));

	/* Setup Tx Queue. */
	CSR_WRITE_1(sc, RB_ADDR(sc_if->msk_txq, RB_CTRL), RB_RST_CLR);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_txq, RB_START),
	    sc->msk_txqstart[sc_if->msk_port] / 8);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_txq, RB_END),
	    sc->msk_txqend[sc_if->msk_port] / 8);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_txq, RB_WP),
	    sc->msk_txqstart[sc_if->msk_port] / 8);
	CSR_WRITE_4(sc, RB_ADDR(sc_if->msk_txq, RB_RP),
	    sc->msk_txqstart[sc_if->msk_port] / 8);
	/* Enable Store & Forward for Tx side. */
	CSR_WRITE_1(sc, RB_ADDR(sc_if->msk_txq, RB_CTRL), RB_ENA_STFWD);
	CSR_WRITE_1(sc, RB_ADDR(sc_if->msk_txq, RB_CTRL), RB_ENA_OP_MD);
	CSR_READ_1(sc, RB_ADDR(sc_if->msk_txq, RB_CTRL));
}
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
struct ath_softc {int /*<<< orphan*/  sc_txbuf_mgmt; int /*<<< orphan*/  sc_txdma_mgmt; int /*<<< orphan*/  sc_txbuf; int /*<<< orphan*/  sc_txdma; int /*<<< orphan*/  sc_tx_desclen; int /*<<< orphan*/  sc_bbuf; int /*<<< orphan*/  sc_bdma; int /*<<< orphan*/  sc_txbuf_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_BCBUF ; 
 int ATH_MAX_SCATTER ; 
 int ATH_TXDESC ; 
 int /*<<< orphan*/  ath_descdma_cleanup (struct ath_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ath_descdma_setup (struct ath_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_txbuf ; 
 int /*<<< orphan*/  ath_txbuf_mgmt ; 

__attribute__((used)) static int
ath_desc_alloc(struct ath_softc *sc)
{
	int error;

	error = ath_descdma_setup(sc, &sc->sc_txdma, &sc->sc_txbuf,
		    "tx", sc->sc_tx_desclen, ath_txbuf, ATH_MAX_SCATTER);
	if (error != 0) {
		return error;
	}
	sc->sc_txbuf_cnt = ath_txbuf;

	error = ath_descdma_setup(sc, &sc->sc_txdma_mgmt, &sc->sc_txbuf_mgmt,
		    "tx_mgmt", sc->sc_tx_desclen, ath_txbuf_mgmt,
		    ATH_TXDESC);
	if (error != 0) {
		ath_descdma_cleanup(sc, &sc->sc_txdma, &sc->sc_txbuf);
		return error;
	}

	/*
	 * XXX mark txbuf_mgmt frames with ATH_BUF_MGMT, so the
	 * flag doesn't have to be set in ath_getbuf_locked().
	 */

	error = ath_descdma_setup(sc, &sc->sc_bdma, &sc->sc_bbuf,
			"beacon", sc->sc_tx_desclen, ATH_BCBUF, 1);
	if (error != 0) {
		ath_descdma_cleanup(sc, &sc->sc_txdma, &sc->sc_txbuf);
		ath_descdma_cleanup(sc, &sc->sc_txdma_mgmt,
		    &sc->sc_txbuf_mgmt);
		return error;
	}
	return 0;
}
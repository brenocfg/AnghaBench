#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  xmit_drain; int /*<<< orphan*/  xmit_handoff; int /*<<< orphan*/  xmit_dma_restart; int /*<<< orphan*/  xmit_attach_comp_func; int /*<<< orphan*/  xmit_teardown; int /*<<< orphan*/  xmit_setup; } ;
struct ath_softc {int sc_tx_desclen; int sc_tx_statuslen; int sc_tx_nmaps; TYPE_1__ sc_tx; } ;
struct ath_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_legacy_attach_comp_func ; 
 int /*<<< orphan*/  ath_legacy_dma_txsetup ; 
 int /*<<< orphan*/  ath_legacy_dma_txteardown ; 
 int /*<<< orphan*/  ath_legacy_tx_dma_restart ; 
 int /*<<< orphan*/  ath_legacy_tx_drain ; 
 int /*<<< orphan*/  ath_legacy_xmit_handoff ; 

void
ath_xmit_setup_legacy(struct ath_softc *sc)
{
	/*
	 * For now, just set the descriptor length to sizeof(ath_desc);
	 * worry about extracting the real length out of the HAL later.
	 */
	sc->sc_tx_desclen = sizeof(struct ath_desc);
	sc->sc_tx_statuslen = sizeof(struct ath_desc);
	sc->sc_tx_nmaps = 1;	/* only one buffer per TX desc */

	sc->sc_tx.xmit_setup = ath_legacy_dma_txsetup;
	sc->sc_tx.xmit_teardown = ath_legacy_dma_txteardown;
	sc->sc_tx.xmit_attach_comp_func = ath_legacy_attach_comp_func;

	sc->sc_tx.xmit_dma_restart = ath_legacy_tx_dma_restart;
	sc->sc_tx.xmit_handoff = ath_legacy_xmit_handoff;

	sc->sc_tx.xmit_drain = ath_legacy_tx_drain;
}
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
struct ath_txq {int axq_qnum; } ;
struct ath_softc {int sc_txqsetup; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TXQ_LOCK_DESTROY (struct ath_txq*) ; 
 int /*<<< orphan*/  ath_hal_releasetxqueue (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ath_tx_cleanupq(struct ath_softc *sc, struct ath_txq *txq)
{

	ath_hal_releasetxqueue(sc->sc_ah, txq->axq_qnum);
	sc->sc_txqsetup &= ~(1<<txq->axq_qnum);
	ATH_TXQ_LOCK_DESTROY(txq);
}
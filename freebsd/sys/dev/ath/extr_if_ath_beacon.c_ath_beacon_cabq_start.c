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
struct ath_txq {int /*<<< orphan*/  axq_q; } ;
struct ath_softc {scalar_t__ sc_isedma; struct ath_txq* sc_cabq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TXQ_LOCK_ASSERT (struct ath_txq*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_beacon_cabq_start_edma (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_beacon_cabq_start_legacy (struct ath_softc*) ; 

void
ath_beacon_cabq_start(struct ath_softc *sc)
{
	struct ath_txq *cabq = sc->sc_cabq;

	ATH_TXQ_LOCK_ASSERT(cabq);

	if (TAILQ_EMPTY(&cabq->axq_q))
		return;

	if (sc->sc_isedma)
		ath_beacon_cabq_start_edma(sc);
	else
		ath_beacon_cabq_start_legacy(sc);
}
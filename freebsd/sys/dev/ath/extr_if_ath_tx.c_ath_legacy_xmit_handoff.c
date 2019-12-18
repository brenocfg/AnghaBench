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
struct ath_txq {scalar_t__ axq_qnum; } ;
struct ath_softc {int /*<<< orphan*/  sc_alq; } ;
struct ath_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_ALQ_EDMA_TXDESC ; 
 scalar_t__ ATH_TXQ_SWQ ; 
 int /*<<< orphan*/  ATH_TX_LOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_tx_alq_post (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_handoff_hw (struct ath_softc*,struct ath_txq*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_handoff_mcast (struct ath_softc*,struct ath_txq*,struct ath_buf*) ; 
 scalar_t__ if_ath_alq_checkdebug (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath_legacy_xmit_handoff(struct ath_softc *sc, struct ath_txq *txq,
    struct ath_buf *bf)
{
	ATH_TX_LOCK_ASSERT(sc);

#ifdef	ATH_DEBUG_ALQ
	if (if_ath_alq_checkdebug(&sc->sc_alq, ATH_ALQ_EDMA_TXDESC))
		ath_tx_alq_post(sc, bf);
#endif

	if (txq->axq_qnum == ATH_TXQ_SWQ)
		ath_tx_handoff_mcast(sc, txq, bf);
	else
		ath_tx_handoff_hw(sc, txq, bf);
}
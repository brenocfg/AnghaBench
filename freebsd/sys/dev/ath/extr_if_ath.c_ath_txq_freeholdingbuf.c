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
struct ath_txq {TYPE_1__* axq_holdingbf; } ;
struct ath_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bf_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_BUF_BUSY ; 
 int /*<<< orphan*/  ATH_TXBUF_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TXBUF_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TXBUF_UNLOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TXQ_LOCK_ASSERT (struct ath_txq*) ; 
 int /*<<< orphan*/  ath_returnbuf_tail (struct ath_softc*,TYPE_1__*) ; 

void
ath_txq_freeholdingbuf(struct ath_softc *sc, struct ath_txq *txq)
{
	ATH_TXBUF_UNLOCK_ASSERT(sc);
	ATH_TXQ_LOCK_ASSERT(txq);

	if (txq->axq_holdingbf == NULL)
		return;

	txq->axq_holdingbf->bf_flags &= ~ATH_BUF_BUSY;

	ATH_TXBUF_LOCK(sc);
	ath_returnbuf_tail(sc, txq->axq_holdingbf);
	ATH_TXBUF_UNLOCK(sc);

	txq->axq_holdingbf = NULL;
}
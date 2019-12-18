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
struct vtnet_txq {int /*<<< orphan*/  vtntx_br; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {int /*<<< orphan*/  vtnet_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_TXQ_LOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  drbr_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_txq_mq_start_locked (struct vtnet_txq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_txq_tq_deferred(void *xtxq, int pending)
{
	struct vtnet_softc *sc;
	struct vtnet_txq *txq;

	txq = xtxq;
	sc = txq->vtntx_sc;

	VTNET_TXQ_LOCK(txq);
	if (!drbr_empty(sc->vtnet_ifp, txq->vtntx_br))
		vtnet_txq_mq_start_locked(txq, NULL);
	VTNET_TXQ_UNLOCK(txq);
}
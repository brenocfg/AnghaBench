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
struct vtnet_txq {int dummy; } ;
struct vtnet_softc {int vtnet_max_vq_pairs; struct vtnet_txq* vtnet_txqs; struct vtnet_rxq* vtnet_rxqs; } ;
struct vtnet_rxq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_RXQ_LOCK (struct vtnet_rxq*) ; 
 int /*<<< orphan*/  VTNET_RXQ_UNLOCK (struct vtnet_rxq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_LOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 

__attribute__((used)) static void
vtnet_stop_rendezvous(struct vtnet_softc *sc)
{
	struct vtnet_rxq *rxq;
	struct vtnet_txq *txq;
	int i;

	/*
	 * Lock and unlock the per-queue mutex so we known the stop
	 * state is visible. Doing only the active queues should be
	 * sufficient, but it does not cost much extra to do all the
	 * queues. Note we hold the core mutex here too.
	 */
	for (i = 0; i < sc->vtnet_max_vq_pairs; i++) {
		rxq = &sc->vtnet_rxqs[i];
		VTNET_RXQ_LOCK(rxq);
		VTNET_RXQ_UNLOCK(rxq);

		txq = &sc->vtnet_txqs[i];
		VTNET_TXQ_LOCK(txq);
		VTNET_TXQ_UNLOCK(txq);
	}
}
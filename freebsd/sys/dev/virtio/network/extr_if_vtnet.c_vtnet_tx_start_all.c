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
struct vtnet_softc {int vtnet_act_vq_pairs; struct vtnet_txq* vtnet_txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_CORE_LOCK_ASSERT (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_TXQ_LOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  vtnet_txq_start (struct vtnet_txq*) ; 

__attribute__((used)) static void
vtnet_tx_start_all(struct vtnet_softc *sc)
{
	struct vtnet_txq *txq;
	int i;

	VTNET_CORE_LOCK_ASSERT(sc);

	for (i = 0; i < sc->vtnet_act_vq_pairs; i++) {
		txq = &sc->vtnet_txqs[i];

		VTNET_TXQ_LOCK(txq);
		vtnet_txq_start(txq);
		VTNET_TXQ_UNLOCK(txq);
	}
}
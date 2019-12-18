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
struct vtnet_txq {int /*<<< orphan*/ * vtntx_tq; } ;
struct vtnet_softc {int vtnet_max_vq_pairs; struct vtnet_txq* vtnet_txqs; struct vtnet_rxq* vtnet_rxqs; } ;
struct vtnet_rxq {int /*<<< orphan*/ * vtnrx_tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_free_taskqueues(struct vtnet_softc *sc)
{
	struct vtnet_rxq *rxq;
	struct vtnet_txq *txq;
	int i;

	for (i = 0; i < sc->vtnet_max_vq_pairs; i++) {
		rxq = &sc->vtnet_rxqs[i];
		if (rxq->vtnrx_tq != NULL) {
			taskqueue_free(rxq->vtnrx_tq);
			rxq->vtnrx_tq = NULL;
		}

		txq = &sc->vtnet_txqs[i];
		if (txq->vtntx_tq != NULL) {
			taskqueue_free(txq->vtntx_tq);
			txq->vtntx_tq = NULL;
		}
	}
}
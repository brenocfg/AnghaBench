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
struct vtnet_txq {scalar_t__ vtntx_watchdog; } ;
struct vtnet_softc {int vtnet_act_vq_pairs; struct vtnet_txq* vtnet_txqs; } ;

/* Variables and functions */

__attribute__((used)) static int
vtnet_init_tx_queues(struct vtnet_softc *sc)
{
	struct vtnet_txq *txq;
	int i;

	for (i = 0; i < sc->vtnet_act_vq_pairs; i++) {
		txq = &sc->vtnet_txqs[i];
		txq->vtntx_watchdog = 0;
	}

	return (0);
}
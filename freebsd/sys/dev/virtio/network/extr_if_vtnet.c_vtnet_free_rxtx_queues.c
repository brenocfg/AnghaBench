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
struct vtnet_softc {int vtnet_max_vq_pairs; int /*<<< orphan*/ * vtnet_txqs; int /*<<< orphan*/ * vtnet_rxqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_destroy_rxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtnet_destroy_txq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_free_rxtx_queues(struct vtnet_softc *sc)
{
	int i;

	if (sc->vtnet_rxqs != NULL) {
		for (i = 0; i < sc->vtnet_max_vq_pairs; i++)
			vtnet_destroy_rxq(&sc->vtnet_rxqs[i]);
		free(sc->vtnet_rxqs, M_DEVBUF);
		sc->vtnet_rxqs = NULL;
	}

	if (sc->vtnet_txqs != NULL) {
		for (i = 0; i < sc->vtnet_max_vq_pairs; i++)
			vtnet_destroy_txq(&sc->vtnet_txqs[i]);
		free(sc->vtnet_txqs, M_DEVBUF);
		sc->vtnet_txqs = NULL;
	}
}
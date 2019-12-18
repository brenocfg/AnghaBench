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
struct pvscsi_softc {int /*<<< orphan*/  msg_ring_dma; scalar_t__ use_msg; int /*<<< orphan*/  cmp_ring_dma; int /*<<< orphan*/  req_ring_dma; int /*<<< orphan*/  rings_state_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvscsi_dma_free (struct pvscsi_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pvscsi_free_rings(struct pvscsi_softc *sc)
{

	pvscsi_dma_free(sc, &sc->rings_state_dma);
	pvscsi_dma_free(sc, &sc->req_ring_dma);
	pvscsi_dma_free(sc, &sc->cmp_ring_dma);
	if (sc->use_msg) {
		pvscsi_dma_free(sc, &sc->msg_ring_dma);
	}
}
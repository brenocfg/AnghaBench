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
typedef  int uint32_t ;
struct pvscsi_softc {int /*<<< orphan*/  sg_list_dma; int /*<<< orphan*/  sense_buffer_dma; int /*<<< orphan*/  buffer_dmat; struct pvscsi_hcb* hcbs; int /*<<< orphan*/  lock; } ;
struct pvscsi_hcb {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvscsi_dma_free (struct pvscsi_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pvscsi_dma_free_per_hcb(struct pvscsi_softc *sc, uint32_t hcbs_allocated)
{
	int i;
	int lock_owned;
	struct pvscsi_hcb *hcb;

	lock_owned = mtx_owned(&sc->lock);

	if (lock_owned) {
		mtx_unlock(&sc->lock);
	}
	for (i = 0; i < hcbs_allocated; ++i) {
		hcb = sc->hcbs + i;
		callout_drain(&hcb->callout);
	};
	if (lock_owned) {
		mtx_lock(&sc->lock);
	}

	for (i = 0; i < hcbs_allocated; ++i) {
		hcb = sc->hcbs + i;
		bus_dmamap_destroy(sc->buffer_dmat, hcb->dma_map);
	};

	pvscsi_dma_free(sc, &sc->sense_buffer_dma);
	pvscsi_dma_free(sc, &sc->sg_list_dma);
}
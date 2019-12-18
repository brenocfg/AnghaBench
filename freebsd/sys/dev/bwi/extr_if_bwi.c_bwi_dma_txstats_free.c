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
struct bwi_txstats_data {int /*<<< orphan*/ * stats_dtag; int /*<<< orphan*/  stats_dmap; int /*<<< orphan*/  stats; int /*<<< orphan*/ * stats_ring_dtag; int /*<<< orphan*/  stats_ring_dmap; int /*<<< orphan*/  stats_ring; } ;
struct bwi_softc {struct bwi_txstats_data* sc_txstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bwi_txstats_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_dma_txstats_free(struct bwi_softc *sc)
{
	struct bwi_txstats_data *st;

	if (sc->sc_txstats == NULL)
		return;
	st = sc->sc_txstats;

	if (st->stats_ring_dtag != NULL) {
		bus_dmamap_unload(st->stats_ring_dtag, st->stats_ring_dmap);
		bus_dmamem_free(st->stats_ring_dtag, st->stats_ring,
				st->stats_ring_dmap);
		bus_dma_tag_destroy(st->stats_ring_dtag);
	}

	if (st->stats_dtag != NULL) {
		bus_dmamap_unload(st->stats_dtag, st->stats_dmap);
		bus_dmamem_free(st->stats_dtag, st->stats, st->stats_dmap);
		bus_dma_tag_destroy(st->stats_dtag);
	}

	free(st, M_DEVBUF);
}
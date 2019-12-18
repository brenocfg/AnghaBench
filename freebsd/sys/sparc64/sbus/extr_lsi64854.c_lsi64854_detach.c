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
struct lsi64854_softc {int /*<<< orphan*/  sc_buffer_dmat; int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/ * setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int L64854_GCSR (struct lsi64854_softc*) ; 
 int L64854_WRITE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lsi64854_detach(struct lsi64854_softc *sc)
{

	if (sc->setup != NULL) {
		bus_dmamap_sync(sc->sc_buffer_dmat, sc->sc_dmamap,
		    (L64854_GCSR(sc) & L64854_WRITE) != 0 ?
		    BUS_DMASYNC_PREREAD : BUS_DMASYNC_PREWRITE);
		bus_dmamap_unload(sc->sc_buffer_dmat, sc->sc_dmamap);
		bus_dmamap_destroy(sc->sc_buffer_dmat, sc->sc_dmamap);
		bus_dma_tag_destroy(sc->sc_buffer_dmat);
	}

	return (0);
}
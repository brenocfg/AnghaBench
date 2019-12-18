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
struct glxsb_softc {int /*<<< orphan*/  sc_dmat; } ;
struct glxsb_dma_map {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
glxsb_dma_free(struct glxsb_softc *sc, struct glxsb_dma_map *dma)
{

	bus_dmamap_unload(sc->sc_dmat, dma->dma_map);
	bus_dmamem_free(sc->sc_dmat, dma->dma_vaddr, dma->dma_map);
	bus_dma_tag_destroy(sc->sc_dmat);
}
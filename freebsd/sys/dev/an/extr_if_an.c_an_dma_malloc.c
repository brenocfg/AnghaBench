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
struct an_softc {int /*<<< orphan*/  an_dtag; } ;
struct an_dma_alloc {int /*<<< orphan*/  an_dma_map; int /*<<< orphan*/  an_dma_vaddr; int /*<<< orphan*/  an_dma_size; int /*<<< orphan*/  an_dma_paddr; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  an_dma_malloc_cb ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
an_dma_malloc(struct an_softc *sc, bus_size_t size, struct an_dma_alloc *dma,
    int mapflags)
{
	int r;

	r = bus_dmamem_alloc(sc->an_dtag, (void**) &dma->an_dma_vaddr,
			     BUS_DMA_NOWAIT, &dma->an_dma_map);
	if (r != 0)
		goto fail_1;

	r = bus_dmamap_load(sc->an_dtag, dma->an_dma_map, dma->an_dma_vaddr,
			    size,
			    an_dma_malloc_cb,
			    &dma->an_dma_paddr,
			    mapflags | BUS_DMA_NOWAIT);
	if (r != 0)
		goto fail_2;

	dma->an_dma_size = size;
	return (0);

fail_2:
	bus_dmamap_unload(sc->an_dtag, dma->an_dma_map);
fail_1:
	bus_dmamem_free(sc->an_dtag, dma->an_dma_vaddr, dma->an_dma_map);
	return (r);
}
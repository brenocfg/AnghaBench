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
struct wpi_softc {int /*<<< orphan*/  sc_dev; } ;
struct wpi_dma_info {void* vaddr; int /*<<< orphan*/  map; int /*<<< orphan*/ * tag; int /*<<< orphan*/  paddr; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpi_dma_contig_free (struct wpi_dma_info*) ; 
 int /*<<< orphan*/  wpi_dma_map_addr ; 

__attribute__((used)) static int
wpi_dma_contig_alloc(struct wpi_softc *sc, struct wpi_dma_info *dma,
    void **kvap, bus_size_t size, bus_size_t alignment)
{
	int error;

	dma->tag = NULL;
	dma->size = size;

	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), alignment,
	    0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL, size,
	    1, size, 0, NULL, NULL, &dma->tag);
	if (error != 0)
		goto fail;

	error = bus_dmamem_alloc(dma->tag, (void **)&dma->vaddr,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO | BUS_DMA_COHERENT, &dma->map);
	if (error != 0)
		goto fail;

	error = bus_dmamap_load(dma->tag, dma->map, dma->vaddr, size,
	    wpi_dma_map_addr, &dma->paddr, BUS_DMA_NOWAIT);
	if (error != 0)
		goto fail;

	bus_dmamap_sync(dma->tag, dma->map, BUS_DMASYNC_PREWRITE);

	if (kvap != NULL)
		*kvap = dma->vaddr;

	return 0;

fail:	wpi_dma_contig_free(dma);
	return error;
}
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
struct iwm_dma_info {int /*<<< orphan*/ * map; int /*<<< orphan*/ * tag; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_dma_contig_free (struct iwm_dma_info*) ; 
 int /*<<< orphan*/  iwm_dma_map_addr ; 

int
iwm_dma_contig_alloc(bus_dma_tag_t tag, struct iwm_dma_info *dma,
    bus_size_t size, bus_size_t alignment)
{
	int error;

	dma->tag = NULL;
	dma->map = NULL;
	dma->size = size;
	dma->vaddr = NULL;

	error = bus_dma_tag_create(tag, alignment,
            0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL, size,
            1, size, 0, NULL, NULL, &dma->tag);
        if (error != 0)
                goto fail;

        error = bus_dmamem_alloc(dma->tag, (void **)&dma->vaddr,
            BUS_DMA_NOWAIT | BUS_DMA_ZERO | BUS_DMA_COHERENT, &dma->map);
        if (error != 0)
                goto fail;

        error = bus_dmamap_load(dma->tag, dma->map, dma->vaddr, size,
            iwm_dma_map_addr, &dma->paddr, BUS_DMA_NOWAIT);
        if (error != 0) {
		bus_dmamem_free(dma->tag, dma->vaddr, dma->map);
		dma->vaddr = NULL;
		goto fail;
	}

	bus_dmamap_sync(dma->tag, dma->map, BUS_DMASYNC_PREWRITE);

	return 0;

fail:
	iwm_dma_contig_free(dma);

	return error;
}
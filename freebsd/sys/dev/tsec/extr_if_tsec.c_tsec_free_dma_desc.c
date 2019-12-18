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
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tsec_free_dma_desc(bus_dma_tag_t dtag, bus_dmamap_t dmap, void *vaddr)
{

	if (vaddr == NULL)
		return;

	/* Unmap descriptors from DMA memory */
	bus_dmamap_sync(dtag, dmap, BUS_DMASYNC_POSTREAD |
	    BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(dtag, dmap);

	/* Free descriptors memory */
	bus_dmamem_free(dtag, vaddr, dmap);

	/* Destroy descriptors tag */
	bus_dma_tag_destroy(dtag);
}
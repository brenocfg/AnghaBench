#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ paddr; int /*<<< orphan*/ * tag; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;
typedef  TYPE_1__* POCE_DMA_MEM ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
oce_dma_free(POCE_SOFTC sc, POCE_DMA_MEM dma)
{
	if (dma->tag == NULL)
		return;

	if (dma->paddr != 0) {
		bus_dmamap_sync(dma->tag, dma->map,
				BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(dma->tag, dma->map);
		dma->paddr = 0;
	}

	if (dma->ptr != NULL) {
		bus_dmamem_free(dma->tag, dma->ptr, dma->map);
		dma->ptr = NULL;
	}

	bus_dma_tag_destroy(dma->tag);
	dma->tag = NULL;
	
	return;
}
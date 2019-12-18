#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bus_size_t ;
struct TYPE_9__ {scalar_t__ paddr; int /*<<< orphan*/  ptr; int /*<<< orphan*/  map; int /*<<< orphan*/  tag; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__* POCE_SOFTC ;
typedef  TYPE_2__* POCE_DMA_MEM ;
typedef  int /*<<< orphan*/  OCE_DMA_MEM ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENXIO ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oce_dma_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  oce_dma_map_addr ; 

int
oce_dma_alloc(POCE_SOFTC sc, bus_size_t size, POCE_DMA_MEM dma, int flags)
{
	int rc;


	memset(dma, 0, sizeof(OCE_DMA_MEM));

	rc = bus_dma_tag_create(bus_get_dma_tag(sc->dev),
				8, 0,
				BUS_SPACE_MAXADDR,
				BUS_SPACE_MAXADDR,
				NULL, NULL,
				size, 1, size, 0, NULL, NULL, &dma->tag);

	if (rc == 0) {
		rc = bus_dmamem_alloc(dma->tag,
				      &dma->ptr,
				      BUS_DMA_NOWAIT | BUS_DMA_COHERENT |
					BUS_DMA_ZERO,
				      &dma->map);
	}

	dma->paddr = 0;
	if (rc == 0) {
		rc = bus_dmamap_load(dma->tag,
				     dma->map,
				     dma->ptr,
				     size,
				     oce_dma_map_addr,
				     &dma->paddr, flags | BUS_DMA_NOWAIT);
		if (dma->paddr == 0)
			rc = ENXIO;
	}

	if (rc != 0)
		oce_dma_free(sc, dma);

	return rc;
}
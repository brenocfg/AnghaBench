#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ndis_softc {int ndis_mmapcnt; int /*<<< orphan*/ * ndis_mmaps; int /*<<< orphan*/  ndis_mtag; int /*<<< orphan*/  ndis_parent_tag; } ;
typedef  int /*<<< orphan*/  ndis_status ;
struct TYPE_4__ {TYPE_1__* nmb_physdeviceobj; } ;
typedef  TYPE_2__ ndis_miniport_block ;
typedef  scalar_t__ ndis_handle ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_3__ {int /*<<< orphan*/  do_devext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int NDIS_MAXSEG ; 
 int /*<<< orphan*/  NDIS_STATUS_RESOURCES ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ndis_status
NdisMAllocateMapRegisters(ndis_handle adapter, uint32_t dmachannel,
    uint8_t dmasize, uint32_t physmapneeded, uint32_t maxmap)
{
	struct ndis_softc	*sc;
	ndis_miniport_block	*block;
	int			error, i, nseg = NDIS_MAXSEG;

	block = (ndis_miniport_block *)adapter;
	sc = device_get_softc(block->nmb_physdeviceobj->do_devext);

	sc->ndis_mmaps = malloc(sizeof(bus_dmamap_t) * physmapneeded,
	    M_DEVBUF, M_NOWAIT|M_ZERO);

	if (sc->ndis_mmaps == NULL)
		return (NDIS_STATUS_RESOURCES);

	error = bus_dma_tag_create(sc->ndis_parent_tag, ETHER_ALIGN, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL,
	    NULL, maxmap * nseg, nseg, maxmap, BUS_DMA_ALLOCNOW,
	    NULL, NULL, &sc->ndis_mtag);

	if (error) {
		free(sc->ndis_mmaps, M_DEVBUF);
		return (NDIS_STATUS_RESOURCES);
	}

	for (i = 0; i < physmapneeded; i++)
		bus_dmamap_create(sc->ndis_mtag, 0, &sc->ndis_mmaps[i]);

	sc->ndis_mmapcnt = physmapneeded;

	return (NDIS_STATUS_SUCCESS);
}
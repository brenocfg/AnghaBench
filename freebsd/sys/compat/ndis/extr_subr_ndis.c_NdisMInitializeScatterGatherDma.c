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
typedef  int /*<<< orphan*/  uint32_t ;
struct ndis_softc {int ndis_sc; int /*<<< orphan*/  ndis_ttag; int /*<<< orphan*/  ndis_parent_tag; } ;
typedef  int /*<<< orphan*/  ndis_status ;
struct TYPE_4__ {TYPE_1__* nmb_physdeviceobj; } ;
typedef  TYPE_2__ ndis_miniport_block ;
typedef  int /*<<< orphan*/ * ndis_handle ;
struct TYPE_3__ {int /*<<< orphan*/  do_devext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int MCLBYTES ; 
 int NDIS_MAXSEG ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ndis_status
NdisMInitializeScatterGatherDma(ndis_handle adapter, uint8_t is64,
    uint32_t maxphysmap)
{
	struct ndis_softc	*sc;
	ndis_miniport_block	*block;
	int			error;

	if (adapter == NULL)
		return (NDIS_STATUS_FAILURE);
	block = (ndis_miniport_block *)adapter;
	sc = device_get_softc(block->nmb_physdeviceobj->do_devext);

	/* Don't do this twice. */
	if (sc->ndis_sc == 1)
		return (NDIS_STATUS_SUCCESS);

	error = bus_dma_tag_create(sc->ndis_parent_tag, ETHER_ALIGN, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES * NDIS_MAXSEG, NDIS_MAXSEG, MCLBYTES, BUS_DMA_ALLOCNOW,
	    NULL, NULL, &sc->ndis_ttag);

	sc->ndis_sc = 1;

	return (NDIS_STATUS_SUCCESS);
}
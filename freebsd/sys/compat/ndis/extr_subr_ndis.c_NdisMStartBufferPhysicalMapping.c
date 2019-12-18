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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct ndis_softc {size_t ndis_mmapcnt; int /*<<< orphan*/  ndis_mtag; int /*<<< orphan*/ * ndis_mmaps; } ;
struct ndis_map_arg {size_t nma_cnt; int /*<<< orphan*/ * nma_fraglist; } ;
typedef  int /*<<< orphan*/  ndis_paddr_unit ;
struct TYPE_4__ {TYPE_1__* nmb_physdeviceobj; } ;
typedef  TYPE_2__ ndis_miniport_block ;
typedef  int /*<<< orphan*/ * ndis_handle ;
typedef  int /*<<< orphan*/  ndis_buffer ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_3__ {int /*<<< orphan*/  do_devext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  MmGetMdlByteCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MmGetMdlVirtualAddress (int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndis_map_cb ; 

__attribute__((used)) static void
NdisMStartBufferPhysicalMapping(ndis_handle adapter, ndis_buffer *buf,
    uint32_t mapreg, uint8_t writedev, ndis_paddr_unit *addrarray,
    uint32_t *arraysize)
{
	ndis_miniport_block	*block;
	struct ndis_softc	*sc;
	struct ndis_map_arg	nma;
	bus_dmamap_t		map;
	int			error;

	if (adapter == NULL)
		return;

	block = (ndis_miniport_block *)adapter;
	sc = device_get_softc(block->nmb_physdeviceobj->do_devext);

	if (mapreg > sc->ndis_mmapcnt)
		return;

	map = sc->ndis_mmaps[mapreg];
	nma.nma_fraglist = addrarray;

	error = bus_dmamap_load(sc->ndis_mtag, map,
	    MmGetMdlVirtualAddress(buf), MmGetMdlByteCount(buf), ndis_map_cb,
	    (void *)&nma, BUS_DMA_NOWAIT);

	if (error)
		return;

	bus_dmamap_sync(sc->ndis_mtag, map,
	    writedev ? BUS_DMASYNC_PREWRITE : BUS_DMASYNC_PREREAD);

	*arraysize = nma.nma_cnt;
}
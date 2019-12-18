#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct siis_dc_cb_args {int /*<<< orphan*/  maddr; scalar_t__ error; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_tag; int /*<<< orphan*/  work_bus; int /*<<< orphan*/  work_map; int /*<<< orphan*/  work; int /*<<< orphan*/  work_tag; } ;
struct siis_channel {TYPE_1__ dma; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int PAGE_SIZE ; 
 int SIIS_MAX_SLOTS ; 
 int SIIS_SG_ENTRIES ; 
 int SIIS_WORK_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct siis_dc_cb_args*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  siis_dmafini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_dmasetupc_cb ; 

__attribute__((used)) static void
siis_dmainit(device_t dev)
{
	struct siis_channel *ch = device_get_softc(dev);
	struct siis_dc_cb_args dcba;

	/* Command area. */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 1024, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, SIIS_WORK_SIZE, 1, SIIS_WORK_SIZE,
	    0, NULL, NULL, &ch->dma.work_tag))
		goto error;
	if (bus_dmamem_alloc(ch->dma.work_tag, (void **)&ch->dma.work, 0,
	    &ch->dma.work_map))
		goto error;
	if (bus_dmamap_load(ch->dma.work_tag, ch->dma.work_map, ch->dma.work,
	    SIIS_WORK_SIZE, siis_dmasetupc_cb, &dcba, 0) || dcba.error) {
		bus_dmamem_free(ch->dma.work_tag, ch->dma.work, ch->dma.work_map);
		goto error;
	}
	ch->dma.work_bus = dcba.maddr;
	/* Data area. */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    SIIS_SG_ENTRIES * PAGE_SIZE * SIIS_MAX_SLOTS,
	    SIIS_SG_ENTRIES, 0xFFFFFFFF,
	    0, busdma_lock_mutex, &ch->mtx, &ch->dma.data_tag)) {
		goto error;
	}
	return;

error:
	device_printf(dev, "WARNING - DMA initialization failed\n");
	siis_dmafini(dev);
}
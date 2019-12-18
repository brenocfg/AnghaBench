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
struct mvs_dc_cb_args {int /*<<< orphan*/  maddr; scalar_t__ error; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_tag; int /*<<< orphan*/  workrp_bus; int /*<<< orphan*/  workrp_map; int /*<<< orphan*/  workrp; int /*<<< orphan*/  workrp_tag; int /*<<< orphan*/  workrq_bus; int /*<<< orphan*/  workrq_map; int /*<<< orphan*/  workrq; int /*<<< orphan*/  workrq_tag; } ;
struct mvs_channel {TYPE_1__ dma; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int MVS_EPRD_MAX ; 
 int MVS_MAX_SLOTS ; 
 int MVS_SG_ENTRIES ; 
 int MVS_WORKRP_SIZE ; 
 int MVS_WORKRQ_SIZE ; 
 int PAGE_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mvs_dc_cb_args*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mvs_dmafini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_dmasetupc_cb ; 

__attribute__((used)) static void
mvs_dmainit(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	struct mvs_dc_cb_args dcba;

	/* EDMA command request area. */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 1024, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, MVS_WORKRQ_SIZE, 1, MVS_WORKRQ_SIZE,
	    0, NULL, NULL, &ch->dma.workrq_tag))
		goto error;
	if (bus_dmamem_alloc(ch->dma.workrq_tag, (void **)&ch->dma.workrq, 0,
	    &ch->dma.workrq_map))
		goto error;
	if (bus_dmamap_load(ch->dma.workrq_tag, ch->dma.workrq_map,
	    ch->dma.workrq, MVS_WORKRQ_SIZE, mvs_dmasetupc_cb, &dcba, 0) ||
	    dcba.error) {
		bus_dmamem_free(ch->dma.workrq_tag,
		    ch->dma.workrq, ch->dma.workrq_map);
		goto error;
	}
	ch->dma.workrq_bus = dcba.maddr;
	/* EDMA command response area. */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 256, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, MVS_WORKRP_SIZE, 1, MVS_WORKRP_SIZE,
	    0, NULL, NULL, &ch->dma.workrp_tag))
		goto error;
	if (bus_dmamem_alloc(ch->dma.workrp_tag, (void **)&ch->dma.workrp, 0,
	    &ch->dma.workrp_map))
		goto error;
	if (bus_dmamap_load(ch->dma.workrp_tag, ch->dma.workrp_map,
	    ch->dma.workrp, MVS_WORKRP_SIZE, mvs_dmasetupc_cb, &dcba, 0) ||
	    dcba.error) {
		bus_dmamem_free(ch->dma.workrp_tag,
		    ch->dma.workrp, ch->dma.workrp_map);
		goto error;
	}
	ch->dma.workrp_bus = dcba.maddr;
	/* Data area. */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 2, MVS_EPRD_MAX,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    MVS_SG_ENTRIES * PAGE_SIZE * MVS_MAX_SLOTS,
	    MVS_SG_ENTRIES, MVS_EPRD_MAX,
	    0, busdma_lock_mutex, &ch->mtx, &ch->dma.data_tag)) {
		goto error;
	}
	return;

error:
	device_printf(dev, "WARNING - DMA initialization failed\n");
	mvs_dmafini(dev);
}
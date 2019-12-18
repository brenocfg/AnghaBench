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
struct ata_request {int flags; TYPE_1__* dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_map; int /*<<< orphan*/  data_tag; int /*<<< orphan*/  sg_map; int /*<<< orphan*/  sg_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEBUG_RQ (struct ata_request*,char*) ; 
 int ATA_R_READ ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ata_dmaunload(struct ata_request *request)
{
    ATA_DEBUG_RQ(request, "dmaunload");

    if (request->dma) {
	bus_dmamap_sync(request->dma->sg_tag, request->dma->sg_map,
			BUS_DMASYNC_POSTWRITE);
	bus_dmamap_sync(request->dma->data_tag, request->dma->data_map,
			(request->flags & ATA_R_READ) ?
			BUS_DMASYNC_POSTREAD : BUS_DMASYNC_POSTWRITE);

	bus_dmamap_unload(request->dma->data_tag, request->dma->data_map);
        request->dma = NULL;
    }
    return 0;
}
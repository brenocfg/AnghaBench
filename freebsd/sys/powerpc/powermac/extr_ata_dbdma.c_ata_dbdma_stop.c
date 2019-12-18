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
typedef  int uint16_t ;
struct ata_request {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ dma; } ;
struct ata_dbdma_channel {TYPE_2__ sc_ch; int /*<<< orphan*/  dbdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int ATA_S_ERROR ; 
 int DBDMA_STATUS_ACTIVE ; 
 int DBDMA_STATUS_DEAD ; 
 int DBDMA_STATUS_RUN ; 
 int /*<<< orphan*/  ata_dbdma_reset (int /*<<< orphan*/ ) ; 
 int dbdma_get_chan_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_pause (int /*<<< orphan*/ ) ; 
 struct ata_dbdma_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ata_dbdma_stop(struct ata_request *request)
{
	struct ata_dbdma_channel *sc = device_get_softc(request->parent);

	uint16_t status;
	
	status = dbdma_get_chan_status(sc->dbdma);

	dbdma_pause(sc->dbdma);
	sc->sc_ch.dma.flags &= ~ATA_DMA_ACTIVE;

	if (status & DBDMA_STATUS_DEAD) {
		device_printf(request->parent,"DBDMA dead, resetting "
		    "channel...\n");
		ata_dbdma_reset(request->parent);
		return ATA_S_ERROR;
	}

	if (!(status & DBDMA_STATUS_RUN)) {
		device_printf(request->parent,"DBDMA confused, stop called "
		    "when channel is not running!\n");
		return ATA_S_ERROR;
	}

	if (status & DBDMA_STATUS_ACTIVE) {
		device_printf(request->parent,"DBDMA channel stopped "
		    "prematurely\n");
		return ATA_S_ERROR;
	}
	return 0;
}
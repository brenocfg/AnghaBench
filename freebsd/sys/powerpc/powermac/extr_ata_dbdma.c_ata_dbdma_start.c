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
struct ata_request {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ dma; } ;
struct ata_dbdma_channel {int /*<<< orphan*/  dbdma; TYPE_2__ sc_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int /*<<< orphan*/  dbdma_wake (int /*<<< orphan*/ ) ; 
 struct ata_dbdma_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_dbdma_start(struct ata_request *request)
{
	struct ata_dbdma_channel *sc = device_get_softc(request->parent);

	sc->sc_ch.dma.flags |= ATA_DMA_ACTIVE;
	dbdma_wake(sc->dbdma);
	return 0;
}
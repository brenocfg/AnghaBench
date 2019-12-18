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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {TYPE_2__ dma; } ;
struct ata_dbdma_channel {int next_dma_slot; int /*<<< orphan*/  dbdma_mtx; TYPE_1__ sc_ch; int /*<<< orphan*/  dbdma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int /*<<< orphan*/  dbdma_insert_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_set_current_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_stop (int /*<<< orphan*/ ) ; 
 struct ata_dbdma_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ata_dbdma_reset(device_t dev)
{
	struct ata_dbdma_channel *sc = device_get_softc(dev);

	mtx_lock(&sc->dbdma_mtx);

	dbdma_stop(sc->dbdma);
	dbdma_insert_stop(sc->dbdma, 0);
	sc->next_dma_slot=1;
	dbdma_set_current_cmd(sc->dbdma, 0);

	sc->sc_ch.dma.flags &= ~ATA_DMA_ACTIVE;

	mtx_unlock(&sc->dbdma_mtx);
}
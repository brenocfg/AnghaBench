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
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ dma; } ;
struct ata_dbdma_channel {int /*<<< orphan*/  dbdma; TYPE_2__ sc_ch; } ;
struct ata_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ALTSTAT ; 
 int ATA_DMA_ACTIVE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int ATA_S_BUSY ; 
 int DBDMA_STATUS_ACTIVE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int dbdma_get_chan_status (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_dbdma_status(device_t dev)
{
	struct ata_dbdma_channel *sc = device_get_softc(dev);
	struct ata_channel *ch = device_get_softc(dev);

	if (sc->sc_ch.dma.flags & ATA_DMA_ACTIVE) {
		return (!(dbdma_get_chan_status(sc->dbdma) & 
		    DBDMA_STATUS_ACTIVE));
	}

	if (ATA_IDX_INB(ch, ATA_ALTSTAT) & ATA_S_BUSY) {
		DELAY(100);
		if (ATA_IDX_INB(ch, ATA_ALTSTAT) & ATA_S_BUSY)
			return 0;
	}
	return 1;
}
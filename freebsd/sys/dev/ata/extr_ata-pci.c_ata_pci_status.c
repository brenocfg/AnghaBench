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
struct ata_pci_controller {int /*<<< orphan*/  legacy; } ;
struct TYPE_2__ {int flags; } ;
struct ata_channel {int flags; TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ALTSTAT ; 
 int ATA_ALWAYS_DMASTAT ; 
 int ATA_BMSTAT_ERROR ; 
 int ATA_BMSTAT_INTERRUPT ; 
 int ATA_BMSTAT_MASK ; 
 int /*<<< orphan*/  ATA_BMSTAT_PORT ; 
 int ATA_DMA_ACTIVE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int ATA_S_BUSY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ dumping ; 

int
ata_pci_status(device_t dev)
{
    struct ata_pci_controller *controller =
	device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);

    if ((dumping || !controller->legacy) &&
	((ch->flags & ATA_ALWAYS_DMASTAT) ||
	 (ch->dma.flags & ATA_DMA_ACTIVE))) {
	int bmstat = ATA_IDX_INB(ch, ATA_BMSTAT_PORT) & ATA_BMSTAT_MASK;

	if ((bmstat & ATA_BMSTAT_INTERRUPT) == 0)
	    return 0;
	ATA_IDX_OUTB(ch, ATA_BMSTAT_PORT, bmstat & ~ATA_BMSTAT_ERROR);
	DELAY(1);
    }
    if (ATA_IDX_INB(ch, ATA_ALTSTAT) & ATA_S_BUSY) {
	DELAY(100);
	if (ATA_IDX_INB(ch, ATA_ALTSTAT) & ATA_S_BUSY)
	    return 0;
    }
    return 1;
}
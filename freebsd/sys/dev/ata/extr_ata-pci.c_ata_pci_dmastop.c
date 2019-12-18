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
struct ata_request {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ata_channel {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BMCMD_PORT ; 
 int ATA_BMCMD_START_STOP ; 
 int ATA_BMSTAT_ERROR ; 
 int ATA_BMSTAT_INTERRUPT ; 
 int ATA_BMSTAT_MASK ; 
 int /*<<< orphan*/  ATA_BMSTAT_PORT ; 
 int /*<<< orphan*/  ATA_DEBUG_RQ (struct ata_request*,char*) ; 
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_pci_dmastop(struct ata_request *request)
{
    struct ata_channel *ch = device_get_softc(request->parent);
    int error;

    ATA_DEBUG_RQ(request, "dmastop");

    ATA_IDX_OUTB(ch, ATA_BMCMD_PORT, 
		 ATA_IDX_INB(ch, ATA_BMCMD_PORT) & ~ATA_BMCMD_START_STOP);
    ch->dma.flags &= ~ATA_DMA_ACTIVE;
    error = ATA_IDX_INB(ch, ATA_BMSTAT_PORT) & ATA_BMSTAT_MASK;
    ATA_IDX_OUTB(ch, ATA_BMSTAT_PORT, ATA_BMSTAT_INTERRUPT | ATA_BMSTAT_ERROR);
    return error;
}
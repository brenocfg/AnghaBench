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
struct ata_request {int flags; int /*<<< orphan*/  parent; } ;
struct ata_pci_controller {int /*<<< orphan*/  r_res1; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ata_channel {TYPE_1__ dma; scalar_t__ unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BMCMD_PORT ; 
 int ATA_BMCMD_START_STOP ; 
 int ATA_BMSTAT_ERROR ; 
 int ATA_BMSTAT_INTERRUPT ; 
 int /*<<< orphan*/  ATA_BMSTAT_PORT ; 
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int ATA_INB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ATA_R_48BIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_promise_dmastop(struct ata_request *request)
{
    struct ata_pci_controller *ctlr=device_get_softc(device_get_parent(request->parent));
    struct ata_channel *ch = device_get_softc(request->parent);
    int error;

    if (request->flags & ATA_R_48BIT) {
	ATA_OUTB(ctlr->r_res1, 0x11,
		 ATA_INB(ctlr->r_res1, 0x11) & ~(ch->unit ? 0x08 : 0x02));
	ATA_OUTL(ctlr->r_res1, ch->unit ? 0x24 : 0x20, 0);
    }
    error = ATA_IDX_INB(ch, ATA_BMSTAT_PORT);
    ATA_IDX_OUTB(ch, ATA_BMCMD_PORT,
		 ATA_IDX_INB(ch, ATA_BMCMD_PORT) & ~ATA_BMCMD_START_STOP);
    ATA_IDX_OUTB(ch, ATA_BMSTAT_PORT, ATA_BMSTAT_INTERRUPT | ATA_BMSTAT_ERROR); 
    ch->dma.flags &= ~ATA_DMA_ACTIVE;
    return error;
}
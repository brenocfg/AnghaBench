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
struct ata_request {int flags; TYPE_1__* dma; int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ata_channel {TYPE_2__ dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  sg_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BMCMD_PORT ; 
 int ATA_BMCMD_START_STOP ; 
 int ATA_BMCMD_WRITE_READ ; 
 int /*<<< orphan*/  ATA_BMDTP_PORT ; 
 int ATA_BMSTAT_ERROR ; 
 int ATA_BMSTAT_INTERRUPT ; 
 int /*<<< orphan*/  ATA_BMSTAT_PORT ; 
 int /*<<< orphan*/  ATA_DEBUG_RQ (struct ata_request*,char*) ; 
 int /*<<< orphan*/  ATA_DMA_ACTIVE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_IDX_OUTL (struct ata_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ATA_R_READ ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_pci_dmastart(struct ata_request *request)
{
    struct ata_channel *ch = device_get_softc(request->parent);

    ATA_DEBUG_RQ(request, "dmastart");

    ATA_IDX_OUTB(ch, ATA_BMSTAT_PORT, (ATA_IDX_INB(ch, ATA_BMSTAT_PORT) | 
		 (ATA_BMSTAT_INTERRUPT | ATA_BMSTAT_ERROR)));
    ATA_IDX_OUTL(ch, ATA_BMDTP_PORT, request->dma->sg_bus);
    ch->dma.flags |= ATA_DMA_ACTIVE;
    ATA_IDX_OUTB(ch, ATA_BMCMD_PORT,
		 (ATA_IDX_INB(ch, ATA_BMCMD_PORT) & ~ATA_BMCMD_WRITE_READ) |
		 ((request->flags & ATA_R_READ) ? ATA_BMCMD_WRITE_READ : 0)|
		 ATA_BMCMD_START_STOP);
    return 0;
}
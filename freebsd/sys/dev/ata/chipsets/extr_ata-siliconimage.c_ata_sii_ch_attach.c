#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ata_pci_controller {TYPE_4__* chip; int /*<<< orphan*/  r_res2; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int boundary; int segsize; } ;
struct ata_channel {int unit; int /*<<< orphan*/  flags; TYPE_3__ hw; TYPE_2__ dma; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {scalar_t__ max_dma; int cfg2; } ;
struct TYPE_5__ {int offset; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 size_t ATA_BMCMD_PORT ; 
 size_t ATA_BMDTP_PORT ; 
 size_t ATA_BMSTAT_PORT ; 
 int /*<<< orphan*/  ATA_CHECKS_CABLE ; 
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_DATA ; 
 size_t ATA_IDX_ADDR ; 
 int /*<<< orphan*/  ATA_KNOWN_PRESENCE ; 
 int /*<<< orphan*/  ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ATA_SA150 ; 
 int /*<<< orphan*/  ATA_SATA ; 
 size_t ATA_SCONTROL ; 
 size_t ATA_SERROR ; 
 size_t ATA_SSTATUS ; 
 int DEV_BSIZE ; 
 int SII_BUG ; 
 int SII_SETCLK ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sii_status ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_sii_ch_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int unit01 = (ch->unit & 1), unit10 = (ch->unit & 2);
    int i;

    for (i = ATA_DATA; i <= ATA_COMMAND; i++) {
	ch->r_io[i].res = ctlr->r_res2;
	ch->r_io[i].offset = 0x80 + i + (unit01 << 6) + (unit10 << 8);
    }
    ch->r_io[ATA_CONTROL].res = ctlr->r_res2;
    ch->r_io[ATA_CONTROL].offset = 0x8a + (unit01 << 6) + (unit10 << 8);
    ch->r_io[ATA_IDX_ADDR].res = ctlr->r_res2;
    ata_default_registers(dev);

    ch->r_io[ATA_BMCMD_PORT].res = ctlr->r_res2;
    ch->r_io[ATA_BMCMD_PORT].offset = 0x00 + (unit01 << 3) + (unit10 << 8);
    ch->r_io[ATA_BMSTAT_PORT].res = ctlr->r_res2;
    ch->r_io[ATA_BMSTAT_PORT].offset = 0x02 + (unit01 << 3) + (unit10 << 8);
    ch->r_io[ATA_BMDTP_PORT].res = ctlr->r_res2;
    ch->r_io[ATA_BMDTP_PORT].offset = 0x04 + (unit01 << 3) + (unit10 << 8);

    if (ctlr->chip->max_dma >= ATA_SA150) {
	ch->r_io[ATA_SSTATUS].res = ctlr->r_res2;
	ch->r_io[ATA_SSTATUS].offset = 0x104 + (unit01 << 7) + (unit10 << 8);
	ch->r_io[ATA_SERROR].res = ctlr->r_res2;
	ch->r_io[ATA_SERROR].offset = 0x108 + (unit01 << 7) + (unit10 << 8);
	ch->r_io[ATA_SCONTROL].res = ctlr->r_res2;
	ch->r_io[ATA_SCONTROL].offset = 0x100 + (unit01 << 7) + (unit10 << 8);
	ch->flags |= ATA_NO_SLAVE;
	ch->flags |= ATA_SATA;
	ch->flags |= ATA_KNOWN_PRESENCE;

	/* enable PHY state change interrupt */
	ATA_OUTL(ctlr->r_res2, 0x148 + (unit01 << 7) + (unit10 << 8),(1 << 16));
    }

    if (ctlr->chip->cfg2 & SII_BUG) {
	/* work around errata in early chips */
	ch->dma.boundary = 8192;
	ch->dma.segsize = 15 * DEV_BSIZE;
    }

    ata_pci_hw(dev);
    ch->hw.status = ata_sii_status;
    if (ctlr->chip->cfg2 & SII_SETCLK)
	ch->flags |= ATA_CHECKS_CABLE;

    ata_pci_dmainit(dev);

    return 0;
}
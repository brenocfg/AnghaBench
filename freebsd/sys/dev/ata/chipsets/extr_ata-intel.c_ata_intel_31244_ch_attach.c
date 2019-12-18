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
struct ata_pci_controller {int /*<<< orphan*/  r_res2; } ;
struct TYPE_4__ {int /*<<< orphan*/  tf_write; int /*<<< orphan*/  status; } ;
struct ata_channel {int unit; TYPE_2__ hw; int /*<<< orphan*/  flags; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int offset; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 size_t ATA_ALTSTAT ; 
 size_t ATA_BMCMD_PORT ; 
 size_t ATA_BMDTP_PORT ; 
 size_t ATA_BMSTAT_PORT ; 
 size_t ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 size_t ATA_COUNT ; 
 size_t ATA_CYL_LSB ; 
 size_t ATA_CYL_MSB ; 
 size_t ATA_DATA ; 
 size_t ATA_DRIVE ; 
 size_t ATA_ERROR ; 
 size_t ATA_FEATURE ; 
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int ATA_MAX_RES ; 
 int /*<<< orphan*/  ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATA_SATA ; 
 size_t ATA_SCONTROL ; 
 size_t ATA_SECTOR ; 
 size_t ATA_SERROR ; 
 size_t ATA_SSTATUS ; 
 size_t ATA_STATUS ; 
 int /*<<< orphan*/  ata_intel_31244_status ; 
 int /*<<< orphan*/  ata_intel_31244_tf_write ; 
 int /*<<< orphan*/  ata_pci_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_intel_31244_ch_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int i;
    int ch_offset;

    ata_pci_dmainit(dev);

    ch_offset = 0x200 + ch->unit * 0x200;

    for (i = ATA_DATA; i < ATA_MAX_RES; i++)
	ch->r_io[i].res = ctlr->r_res2;

    /* setup ATA registers */
    ch->r_io[ATA_DATA].offset = ch_offset + 0x00;
    ch->r_io[ATA_FEATURE].offset = ch_offset + 0x06;
    ch->r_io[ATA_COUNT].offset = ch_offset + 0x08;
    ch->r_io[ATA_SECTOR].offset = ch_offset + 0x0c;
    ch->r_io[ATA_CYL_LSB].offset = ch_offset + 0x10;
    ch->r_io[ATA_CYL_MSB].offset = ch_offset + 0x14;
    ch->r_io[ATA_DRIVE].offset = ch_offset + 0x18;
    ch->r_io[ATA_COMMAND].offset = ch_offset + 0x1d;
    ch->r_io[ATA_ERROR].offset = ch_offset + 0x04;
    ch->r_io[ATA_STATUS].offset = ch_offset + 0x1c;
    ch->r_io[ATA_ALTSTAT].offset = ch_offset + 0x28;
    ch->r_io[ATA_CONTROL].offset = ch_offset + 0x29;

    /* setup DMA registers */
    ch->r_io[ATA_SSTATUS].offset = ch_offset + 0x100;
    ch->r_io[ATA_SERROR].offset = ch_offset + 0x104;
    ch->r_io[ATA_SCONTROL].offset = ch_offset + 0x108;

    /* setup SATA registers */
    ch->r_io[ATA_BMCMD_PORT].offset = ch_offset + 0x70;
    ch->r_io[ATA_BMSTAT_PORT].offset = ch_offset + 0x72;
    ch->r_io[ATA_BMDTP_PORT].offset = ch_offset + 0x74;

    ch->flags |= ATA_NO_SLAVE;
    ch->flags |= ATA_SATA;
    ata_pci_hw(dev);
    ch->hw.status = ata_intel_31244_status;
    ch->hw.tf_write = ata_intel_31244_tf_write;

    /* enable PHY state change interrupt */
    ATA_OUTL(ctlr->r_res2, 0x4,
	     ATA_INL(ctlr->r_res2, 0x04) | (0x01 << (ch->unit << 3)));
    return 0;
}
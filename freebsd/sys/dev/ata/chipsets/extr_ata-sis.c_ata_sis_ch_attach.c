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
struct ata_pci_controller {int /*<<< orphan*/  r_res2; TYPE_1__* chip; } ;
struct ata_channel {int unit; int /*<<< orphan*/  flags; TYPE_2__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  res; } ;
struct TYPE_3__ {scalar_t__ chipid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_SATA ; 
 size_t ATA_SCONTROL ; 
 size_t ATA_SERROR ; 
 scalar_t__ ATA_SIS182 ; 
 size_t ATA_SSTATUS ; 
 int ENXIO ; 
 scalar_t__ ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_sis_ch_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int offset = ch->unit << ((ctlr->chip->chipid == ATA_SIS182) ? 5 : 6);

    /* setup the usual register normal pci style */
    if (ata_pci_ch_attach(dev))
	return ENXIO;

    ch->r_io[ATA_SSTATUS].res = ctlr->r_res2;
    ch->r_io[ATA_SSTATUS].offset = 0x00 + offset;
    ch->r_io[ATA_SERROR].res = ctlr->r_res2;
    ch->r_io[ATA_SERROR].offset = 0x04 + offset;
    ch->r_io[ATA_SCONTROL].res = ctlr->r_res2;
    ch->r_io[ATA_SCONTROL].offset = 0x08 + offset;
    ch->flags |= ATA_NO_SLAVE;
    ch->flags |= ATA_SATA;

    /* XXX SOS PHY hotplug handling missing in SiS chip ?? */
    /* XXX SOS unknown how to enable PHY state change interrupt */
    return 0;
}
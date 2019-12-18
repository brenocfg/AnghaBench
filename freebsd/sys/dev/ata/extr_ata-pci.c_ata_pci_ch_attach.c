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
struct resource {int dummy; } ;
struct ata_pci_controller {struct resource* r_res1; scalar_t__ legacy; } ;
struct ata_channel {int unit; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int offset; struct resource* res; } ;

/* Variables and functions */
 int ATA_BMCMD_PORT ; 
 int ATA_BMDTP_PORT ; 
 int ATA_BMIOSIZE ; 
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_CTLADDR_RID ; 
 int ATA_DATA ; 
 size_t ATA_IDX_ADDR ; 
 int ATA_IOADDR_RID ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_hw (int /*<<< orphan*/ ) ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

int
ata_pci_ch_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    struct resource *io = NULL, *ctlio = NULL;
    int i, rid;

    rid = ATA_IOADDR_RID;
    if (!(io = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE)))
	return ENXIO;

    rid = ATA_CTLADDR_RID;
    if (!(ctlio = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,RF_ACTIVE))){
	bus_release_resource(dev, SYS_RES_IOPORT, ATA_IOADDR_RID, io);
	return ENXIO;
    }

    ata_pci_dmainit(dev);

    for (i = ATA_DATA; i <= ATA_COMMAND; i ++) {
	ch->r_io[i].res = io;
	ch->r_io[i].offset = i;
    }
    ch->r_io[ATA_CONTROL].res = ctlio;
    ch->r_io[ATA_CONTROL].offset = ctlr->legacy ? 0 : 2;
    ch->r_io[ATA_IDX_ADDR].res = io;
    ata_default_registers(dev);
    if (ctlr->r_res1) {
	for (i = ATA_BMCMD_PORT; i <= ATA_BMDTP_PORT; i++) {
	    ch->r_io[i].res = ctlr->r_res1;
	    ch->r_io[i].offset = (i - ATA_BMCMD_PORT) + (ch->unit*ATA_BMIOSIZE);
	}
    }

    ata_pci_hw(dev);
    return 0;
}
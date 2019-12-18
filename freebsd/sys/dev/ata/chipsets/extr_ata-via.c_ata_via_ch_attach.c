#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct ata_pci_controller {TYPE_2__* chip; struct resource* r_res2; struct resource* r_res1; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct ata_channel {int unit; int /*<<< orphan*/  flags; TYPE_3__ hw; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int cfg2; int cfg1; } ;
struct TYPE_4__ {int offset; struct resource* res; } ;

/* Variables and functions */
 int ATA_BMCMD_PORT ; 
 int ATA_BMDTP_PORT ; 
 int ATA_BMIOSIZE ; 
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_DATA ; 
 size_t ATA_IDX_ADDR ; 
 int ATA_IOSIZE ; 
 int /*<<< orphan*/  ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_PERIODIC_POLL ; 
 int /*<<< orphan*/  ATA_SATA ; 
 size_t ATA_SCONTROL ; 
 size_t ATA_SERROR ; 
 size_t ATA_SSTATUS ; 
 int ENXIO ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int VIABAR ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sata_scr_write (struct ata_channel*,int,size_t,int) ; 
 int /*<<< orphan*/  ata_via_status ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_via_ch_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);

    /* newer SATA chips has resources in one BAR for each channel */
    if (ctlr->chip->cfg2 & VIABAR) {
	struct resource *r_io;
	int i, rid;
		
	ata_pci_dmainit(dev);

	rid = PCIR_BAR(ch->unit);
	if (!(r_io = bus_alloc_resource_any(device_get_parent(dev),
					    SYS_RES_IOPORT,
					    &rid, RF_ACTIVE)))
	    return ENXIO;

	for (i = ATA_DATA; i <= ATA_COMMAND; i ++) {
	    ch->r_io[i].res = r_io;
	    ch->r_io[i].offset = i;
	}
	ch->r_io[ATA_CONTROL].res = r_io;
	ch->r_io[ATA_CONTROL].offset = 2 + ATA_IOSIZE;
	ch->r_io[ATA_IDX_ADDR].res = r_io;
	ata_default_registers(dev);
	for (i = ATA_BMCMD_PORT; i <= ATA_BMDTP_PORT; i++) {
	    ch->r_io[i].res = ctlr->r_res1;
	    ch->r_io[i].offset = (i - ATA_BMCMD_PORT)+(ch->unit * ATA_BMIOSIZE);
	}
	ata_pci_hw(dev);
	if (ch->unit >= 2)
	    return 0;
    }
    else {
	/* setup the usual register normal pci style */
	if (ata_pci_ch_attach(dev))
	    return ENXIO;
    }

    ch->r_io[ATA_SSTATUS].res = ctlr->r_res2;
    ch->r_io[ATA_SSTATUS].offset = (ch->unit << ctlr->chip->cfg1);
    ch->r_io[ATA_SERROR].res = ctlr->r_res2;
    ch->r_io[ATA_SERROR].offset = 0x04 + (ch->unit << ctlr->chip->cfg1);
    ch->r_io[ATA_SCONTROL].res = ctlr->r_res2;
    ch->r_io[ATA_SCONTROL].offset = 0x08 + (ch->unit << ctlr->chip->cfg1);
    ch->hw.status = ata_via_status;
    ch->flags |= ATA_NO_SLAVE;
    ch->flags |= ATA_SATA;
    ch->flags |= ATA_PERIODIC_POLL;

    ata_sata_scr_write(ch, -1, ATA_SERROR, 0xffffffff);

    return 0;
}
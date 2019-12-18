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
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {TYPE_2__* r_io; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  res; } ;
struct TYPE_3__ {int cfg2; } ;

/* Variables and functions */
 size_t ATA_CONTROL ; 
 int ENXIO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int VIABAR ; 
 scalar_t__ ata_pci_ch_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_dmafini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_via_ch_detach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);

    /* newer SATA chips has resources in one BAR for each channel */
    if (ctlr->chip->cfg2 & VIABAR) {
	int rid;
		
	rid = PCIR_BAR(ch->unit);
	bus_release_resource(device_get_parent(dev),
	    SYS_RES_IOPORT, rid, ch->r_io[ATA_CONTROL].res);

	ata_pci_dmafini(dev);
    }
    else {
	/* setup the usual register normal pci style */
	if (ata_pci_ch_detach(dev))
	    return ENXIO;
    }

    return 0;
}
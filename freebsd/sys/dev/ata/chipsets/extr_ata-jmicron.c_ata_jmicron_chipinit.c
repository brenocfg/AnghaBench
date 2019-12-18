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
struct ata_pci_controller {TYPE_1__* chip; int /*<<< orphan*/  channels; void* setmode; void* reset; void* ch_detach; void* ch_attach; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfg2; scalar_t__ cfg1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 void* ata_generic_reset ; 
 void* ata_jmicron_ch_attach ; 
 void* ata_jmicron_setmode ; 
 void* ata_pci_ch_detach ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,void*) ; 
 int pci_read_config (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int
ata_jmicron_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    device_t child;

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    /* do we have multiple PCI functions ? */
    if (pci_read_config(dev, 0xdf, 1) & 0x40) {
	/* If this was not claimed by AHCI, then we are on the PATA part */
	ctlr->ch_attach = ata_jmicron_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->reset = ata_generic_reset;
	ctlr->setmode = ata_jmicron_setmode;
	ctlr->channels = ctlr->chip->cfg2;
    }
    else {
	/* set controller configuration to a combined setup we support */
	pci_write_config(dev, 0x40, 0x80c0a131, 4);
	pci_write_config(dev, 0x80, 0x01200000, 4);
	/* Create AHCI subdevice if AHCI part present. */
	if (ctlr->chip->cfg1) {
	    	child = device_add_child(dev, NULL, -1);
		if (child != NULL) {
		    device_set_ivars(child, (void *)(intptr_t)-1);
		    bus_generic_attach(dev);
		}
	}
	ctlr->ch_attach = ata_jmicron_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->reset = ata_generic_reset;
	ctlr->setmode = ata_jmicron_setmode;
	ctlr->channels = ctlr->chip->cfg2;
    }
    return 0;
}
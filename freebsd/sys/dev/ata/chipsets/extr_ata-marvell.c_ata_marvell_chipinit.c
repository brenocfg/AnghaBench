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
struct ata_pci_controller {int channels; int /*<<< orphan*/  setmode; int /*<<< orphan*/  reset; int /*<<< orphan*/  ch_detach; int /*<<< orphan*/  ch_attach; TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {scalar_t__ cfg1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 int /*<<< orphan*/  ata_generic_reset ; 
 int /*<<< orphan*/  ata_marvell_ch_attach ; 
 int /*<<< orphan*/  ata_marvell_setmode ; 
 int /*<<< orphan*/  ata_pci_ch_detach ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int
ata_marvell_chipinit(device_t dev)
{
	struct ata_pci_controller *ctlr = device_get_softc(dev);
	device_t child;

	if (ata_setup_interrupt(dev, ata_generic_intr))
		return ENXIO;
	/* Create AHCI subdevice if AHCI part present. */
	if (ctlr->chip->cfg1) {
	    	child = device_add_child(dev, NULL, -1);
		if (child != NULL) {
		    device_set_ivars(child, (void *)(intptr_t)-1);
		    bus_generic_attach(dev);
		}
	}
        ctlr->ch_attach = ata_marvell_ch_attach;
	ctlr->ch_detach = ata_pci_ch_detach;
	ctlr->reset = ata_generic_reset;
        ctlr->setmode = ata_marvell_setmode;
        ctlr->channels = 1;
        return (0);
}
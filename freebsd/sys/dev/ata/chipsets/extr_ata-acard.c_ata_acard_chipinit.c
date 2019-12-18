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
struct ata_pci_controller {int channels; int /*<<< orphan*/  setmode; TYPE_1__* chip; int /*<<< orphan*/  ch_detach; int /*<<< orphan*/  ch_attach; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ cfg1; } ;

/* Variables and functions */
 scalar_t__ ATP_OLD ; 
 int ENXIO ; 
 int /*<<< orphan*/  ata_acard_850_setmode ; 
 int /*<<< orphan*/  ata_acard_86X_setmode ; 
 int /*<<< orphan*/  ata_acard_ch_attach ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 int /*<<< orphan*/  ata_pci_ch_detach ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ata_acard_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    ctlr->ch_attach = ata_acard_ch_attach;
    ctlr->ch_detach = ata_pci_ch_detach;
    if (ctlr->chip->cfg1 == ATP_OLD) {
	ctlr->setmode = ata_acard_850_setmode;
	/* Work around the lack of channel serialization in ATA_CAM. */
	ctlr->channels = 1;
	device_printf(dev, "second channel ignored\n");
    }
    else
	ctlr->setmode = ata_acard_86X_setmode;
    return 0;
}
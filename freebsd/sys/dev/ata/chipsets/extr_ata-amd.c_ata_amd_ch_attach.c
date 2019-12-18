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
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg1; } ;

/* Variables and functions */
 int AMD_CABLE ; 
 int /*<<< orphan*/  ATA_CHECKS_CABLE ; 
 int ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_amd_ch_attach(device_t dev)
{
	struct ata_pci_controller *ctlr;
	struct ata_channel *ch;
	int error;

	ctlr = device_get_softc(device_get_parent(dev));
	ch = device_get_softc(dev);
	error = ata_pci_ch_attach(dev);
	if (ctlr->chip->cfg1 & AMD_CABLE)
		ch->flags |= ATA_CHECKS_CABLE;
	return (error);
}
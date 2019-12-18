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
struct ata_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BMDEVSPEC_0 ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int ATA_UDMA2 ; 
 scalar_t__ ata_dma_check_80pin ; 
 int /*<<< orphan*/  ata_print_cable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_marvell_setmode(device_t dev, int target, int mode)
{
	struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
	struct ata_channel *ch = device_get_softc(dev);

	mode = min(mode, ctlr->chip->max_dma);
	/* Check for 80pin cable present. */
	if (ata_dma_check_80pin && mode > ATA_UDMA2 &&
	    ATA_IDX_INB(ch, ATA_BMDEVSPEC_0) & 0x01) {
		ata_print_cable(dev, "controller");
		mode = ATA_UDMA2;
	}
	/* Nothing to do to setup mode, the controller snoop SET_FEATURE cmd. */
	return (mode);
}
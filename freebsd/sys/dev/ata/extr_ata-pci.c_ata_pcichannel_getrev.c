#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ata_pci_controller {int (* getrev ) (int /*<<< orphan*/ ,int) ;} ;
struct ata_channel {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_SATA ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ata_pcichannel_getrev(device_t dev, int target)
{
	struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
	struct ata_channel *ch = device_get_softc(dev);

	if (ch->flags & ATA_SATA) {
		if (ctlr->getrev)
			return (ctlr->getrev(dev, target));
		else 
			return (0xff);
	} else
		return (0);
}
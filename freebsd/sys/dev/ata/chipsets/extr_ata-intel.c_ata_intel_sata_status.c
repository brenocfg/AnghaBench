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
struct ata_channel {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_NO_SLAVE ; 
 int ata_pci_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sata_phy_check_events (int /*<<< orphan*/ ,int) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_intel_sata_status(device_t dev)
{
	struct ata_channel *ch = device_get_softc(dev);

	ata_sata_phy_check_events(dev, 0);
	if ((ch->flags & ATA_NO_SLAVE) == 0)
		ata_sata_phy_check_events(dev, 1);

	return ata_pci_status(dev);
}
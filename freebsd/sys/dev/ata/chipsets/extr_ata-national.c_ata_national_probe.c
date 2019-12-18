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
struct ata_pci_controller {int /*<<< orphan*/  chipinit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ATA_SC1100 ; 
 int BUS_PROBE_LOW_PRIORITY ; 
 int ENXIO ; 
 int /*<<< orphan*/  ata_national_chipinit ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_national_probe(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    /* this chip is a clone of the Cyrix chip, bugs and all */
    if (pci_get_devid(dev) == ATA_SC1100) {
	device_set_desc(dev, "National Geode SC1100 ATA33 controller");
	ctlr->chipinit = ata_national_chipinit;
	return (BUS_PROBE_LOW_PRIORITY);
    }
    return ENXIO;
}
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
 scalar_t__ ATA_MICRON_RZ1000 ; 
 scalar_t__ ATA_MICRON_RZ1001 ; 
 int BUS_PROBE_LOW_PRIORITY ; 
 int ENXIO ; 
 int /*<<< orphan*/  ata_generic_chipinit ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_micron_probe(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    if (pci_get_devid(dev) == ATA_MICRON_RZ1000 ||
	pci_get_devid(dev) == ATA_MICRON_RZ1001) {
	device_set_desc(dev,
	    "RZ 100? ATA controller !WARNING! data loss/corruption risk");
	ctlr->chipinit = ata_generic_chipinit;
	return (BUS_PROBE_LOW_PRIORITY);
    }
    return (ENXIO);
}
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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 scalar_t__ PCIC_STORAGE ; 
 scalar_t__ PCIS_STORAGE_IDE ; 
 int /*<<< orphan*/  ata_generic_chipinit ; 
 char* ata_pcivendor2str (int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

int
ata_pci_probe(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    char buffer[64];

    /* is this a storage class device ? */
    if (pci_get_class(dev) != PCIC_STORAGE)
	return (ENXIO);

    /* is this an IDE/ATA type device ? */
    if (pci_get_subclass(dev) != PCIS_STORAGE_IDE)
	return (ENXIO);
    
    sprintf(buffer, "%s ATA controller", ata_pcivendor2str(dev));
    device_set_desc_copy(dev, buffer);
    ctlr->chipinit = ata_generic_chipinit;

    /* we are a low priority handler */
    return (BUS_PROBE_GENERIC);
}
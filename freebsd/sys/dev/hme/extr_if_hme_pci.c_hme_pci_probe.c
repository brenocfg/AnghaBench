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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ PCI_PRODUCT_SUN_HMENETWORK ; 
 scalar_t__ PCI_VENDOR_SUN ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

int
hme_pci_probe(device_t dev)
{

	if (pci_get_vendor(dev) == PCI_VENDOR_SUN &&
	    pci_get_device(dev) == PCI_PRODUCT_SUN_HMENETWORK) {
		device_set_desc(dev, "Sun HME 10/100 Ethernet");
		return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}
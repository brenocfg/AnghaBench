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
 scalar_t__ PCI_PRODUCT_SAFEXCEL ; 
 scalar_t__ PCI_VENDOR_SAFENET ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
safe_probe(device_t dev)
{
	if (pci_get_vendor(dev) == PCI_VENDOR_SAFENET &&
	    pci_get_device(dev) == PCI_PRODUCT_SAFEXCEL)
		return (BUS_PROBE_DEFAULT);
	return (ENXIO);
}
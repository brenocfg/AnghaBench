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
 scalar_t__ PCI_PRODUCT_BLUESTEEL_5501 ; 
 scalar_t__ PCI_PRODUCT_BLUESTEEL_5601 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5801 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5802 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5805 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5820 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5821 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5822 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5823 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5825 ; 
 scalar_t__ PCI_PRODUCT_SUN_5821 ; 
 scalar_t__ PCI_PRODUCT_SUN_SCA1K ; 
 scalar_t__ PCI_VENDOR_BLUESTEEL ; 
 scalar_t__ PCI_VENDOR_BROADCOM ; 
 scalar_t__ PCI_VENDOR_SUN ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ubsec_probe(device_t dev)
{
	if (pci_get_vendor(dev) == PCI_VENDOR_SUN &&
	    (pci_get_device(dev) == PCI_PRODUCT_SUN_5821 ||
	     pci_get_device(dev) == PCI_PRODUCT_SUN_SCA1K))
		return (BUS_PROBE_DEFAULT);
	if (pci_get_vendor(dev) == PCI_VENDOR_BLUESTEEL &&
	    (pci_get_device(dev) == PCI_PRODUCT_BLUESTEEL_5501 ||
	     pci_get_device(dev) == PCI_PRODUCT_BLUESTEEL_5601))
		return (BUS_PROBE_DEFAULT);
	if (pci_get_vendor(dev) == PCI_VENDOR_BROADCOM &&
	    (pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5801 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5802 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5805 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5820 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5821 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5822 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5823 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5825
	     ))
		return (BUS_PROBE_DEFAULT);
	return (ENXIO);
}
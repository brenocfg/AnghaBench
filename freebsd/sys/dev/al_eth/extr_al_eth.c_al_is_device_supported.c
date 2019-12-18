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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_AL_ETH ; 
 scalar_t__ PCI_DEVICE_ID_AL_ETH_ADVANCED ; 
 scalar_t__ PCI_DEVICE_ID_AL_ETH_FPGA_NIC ; 
 scalar_t__ PCI_DEVICE_ID_AL_ETH_NIC ; 
 scalar_t__ PCI_VENDOR_ID_ANNAPURNA_LABS ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_is_device_supported(device_t dev)
{
	uint16_t pci_vendor_id = pci_get_vendor(dev);
	uint16_t pci_device_id = pci_get_device(dev);

	return (pci_vendor_id == PCI_VENDOR_ID_ANNAPURNA_LABS &&
	    (pci_device_id == PCI_DEVICE_ID_AL_ETH ||
	    pci_device_id == PCI_DEVICE_ID_AL_ETH_ADVANCED ||
	    pci_device_id == PCI_DEVICE_ID_AL_ETH_NIC ||
	    pci_device_id == PCI_DEVICE_ID_AL_ETH_FPGA_NIC));
}
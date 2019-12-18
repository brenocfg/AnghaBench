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
typedef  int u32 ;
struct pci_dev {scalar_t__ msi_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_MSI_ADDRESS_HI ; 
 scalar_t__ PCI_MSI_ADDRESS_LO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static void rtas_hack_32bit_msi_gen2(struct pci_dev *pdev)
{
	u32 addr_hi, addr_lo;

	/*
	 * We should only get in here for IODA1 configs. This is based on the
	 * fact that we using RTAS for MSIs, we don't have the 32 bit MSI RTAS
	 * support, and we are in a PCIe Gen2 slot.
	 */
	dev_info(&pdev->dev,
		 "rtas_msi: No 32 bit MSI firmware support, forcing 32 bit MSI\n");
	pci_read_config_dword(pdev, pdev->msi_cap + PCI_MSI_ADDRESS_HI, &addr_hi);
	addr_lo = 0xffff0000 | ((addr_hi >> (48 - 32)) << 4);
	pci_write_config_dword(pdev, pdev->msi_cap + PCI_MSI_ADDRESS_LO, addr_lo);
	pci_write_config_dword(pdev, pdev->msi_cap + PCI_MSI_ADDRESS_HI, 0);
}
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
typedef  int u64 ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {int /*<<< orphan*/  dn; } ;

/* Variables and functions */
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 find_u4_magic_addr(struct pci_dev *pdev, unsigned int hwirq)
{
	struct pci_controller *hose = pci_bus_to_host(pdev->bus);

	/* U4 PCIe MSIs need to write to the special register in
	 * the bridge that generates interrupts. There should be
	 * theorically a register at 0xf8005000 where you just write
	 * the MSI number and that triggers the right interrupt, but
	 * unfortunately, this is busted in HW, the bridge endian swaps
	 * the value and hits the wrong nibble in the register.
	 *
	 * So instead we use another register set which is used normally
	 * for converting HT interrupts to MPIC interrupts, which decodes
	 * the interrupt number as part of the low address bits
	 *
	 * This will not work if we ever use more than one legacy MSI in
	 * a block but we never do. For one MSI or multiple MSI-X where
	 * each interrupt address can be specified separately, it works
	 * just fine.
	 */
	if (of_device_is_compatible(hose->dn, "u4-pcie") ||
	    of_device_is_compatible(hose->dn, "U4-pcie"))
		return 0xf8004000 | (hwirq << 4);

	return 0;
}
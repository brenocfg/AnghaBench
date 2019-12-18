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
typedef  scalar_t__ u32 ;
struct ar2315_pci_ctrl {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR2315_PCI_HOST_DEVID ; 
 int AR2315_PCI_HOST_MBAR0 ; 
 int AR2315_PCI_HOST_MBAR1 ; 
 int AR2315_PCI_HOST_MBAR2 ; 
 int /*<<< orphan*/  AR2315_PCI_HOST_SLOT ; 
 int ENODEV ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_2 ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_FAST_BACK ; 
 int PCI_COMMAND_INVALIDATE ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int PCI_COMMAND_SPECIAL ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int ar2315_pci_local_cfg_rd (struct ar2315_pci_ctrl*,unsigned int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ar2315_pci_local_cfg_wr (struct ar2315_pci_ctrl*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar2315_pci_host_setup(struct ar2315_pci_ctrl *apc)
{
	unsigned devfn = PCI_DEVFN(AR2315_PCI_HOST_SLOT, 0);
	int res;
	u32 id;

	res = ar2315_pci_local_cfg_rd(apc, devfn, PCI_VENDOR_ID, &id);
	if (res != PCIBIOS_SUCCESSFUL || id != AR2315_PCI_HOST_DEVID)
		return -ENODEV;

	/* Program MBARs */
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_BASE_ADDRESS_0,
				AR2315_PCI_HOST_MBAR0);
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_BASE_ADDRESS_1,
				AR2315_PCI_HOST_MBAR1);
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_BASE_ADDRESS_2,
				AR2315_PCI_HOST_MBAR2);

	/* Run */
	ar2315_pci_local_cfg_wr(apc, devfn, PCI_COMMAND, PCI_COMMAND_MEMORY |
				PCI_COMMAND_MASTER | PCI_COMMAND_SPECIAL |
				PCI_COMMAND_INVALIDATE | PCI_COMMAND_PARITY |
				PCI_COMMAND_SERR | PCI_COMMAND_FAST_BACK);

	return 0;
}
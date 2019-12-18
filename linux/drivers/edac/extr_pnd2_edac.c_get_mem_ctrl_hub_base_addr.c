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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct b_cr_mchbar_lo_pci {int /*<<< orphan*/  base; int /*<<< orphan*/  enable; } ;
struct b_cr_mchbar_hi_pci {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int U64_LSHIFT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 get_mem_ctrl_hub_base_addr(void)
{
	struct b_cr_mchbar_lo_pci lo;
	struct b_cr_mchbar_hi_pci hi;
	struct pci_dev *pdev;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x1980, NULL);
	if (pdev) {
		pci_read_config_dword(pdev, 0x48, (u32 *)&lo);
		pci_read_config_dword(pdev, 0x4c, (u32 *)&hi);
		pci_dev_put(pdev);
	} else {
		return 0;
	}

	if (!lo.enable) {
		edac_dbg(2, "MMIO via memory controller hub base address is disabled!\n");
		return 0;
	}

	return U64_LSHIFT(hi.base, 32) | U64_LSHIFT(lo.base, 15);
}
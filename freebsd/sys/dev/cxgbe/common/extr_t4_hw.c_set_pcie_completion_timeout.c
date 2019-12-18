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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 scalar_t__ PCI_EXP_DEVCTL2 ; 
 scalar_t__ t4_os_find_pci_capability (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_os_pci_read_cfg2 (struct adapter*,scalar_t__,int*) ; 
 int /*<<< orphan*/  t4_os_pci_write_cfg2 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void set_pcie_completion_timeout(struct adapter *adapter,
						  u8 range)
{
	u16 val;
	u32 pcie_cap;

	pcie_cap = t4_os_find_pci_capability(adapter, PCI_CAP_ID_EXP);
	if (pcie_cap) {
		t4_os_pci_read_cfg2(adapter, pcie_cap + PCI_EXP_DEVCTL2, &val);
		val &= 0xfff0;
		val |= range ;
		t4_os_pci_write_cfg2(adapter, pcie_cap + PCI_EXP_DEVCTL2, val);
	}
}
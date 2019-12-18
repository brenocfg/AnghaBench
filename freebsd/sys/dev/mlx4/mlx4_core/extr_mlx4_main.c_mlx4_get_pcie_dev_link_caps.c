#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mlx4_dev {TYPE_1__* persist; } ;
typedef  enum pcie_link_width { ____Placeholder_pcie_link_width } pcie_link_width ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCIE_LNK_WIDTH_UNKNOWN ; 
 int PCIE_MLW_CAP_SHIFT ; 
 int PCIE_SPEED_2_5GT ; 
 int PCIE_SPEED_5_0GT ; 
 int PCIE_SPEED_8_0GT ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP2 ; 
 int PCI_EXP_LNKCAP2_SLS_2_5GB ; 
 int PCI_EXP_LNKCAP2_SLS_5_0GB ; 
 int PCI_EXP_LNKCAP2_SLS_8_0GB ; 
 int PCI_EXP_LNKCAP_MLW ; 
 int PCI_EXP_LNKCAP_SLS_2_5GB ; 
 int PCI_EXP_LNKCAP_SLS_5_0GB ; 
 int PCI_SPEED_UNKNOWN ; 
 int pcie_capability_read_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mlx4_get_pcie_dev_link_caps(struct mlx4_dev *dev,
				       enum pci_bus_speed *speed,
				       enum pcie_link_width *width)
{
	u32 lnkcap1, lnkcap2;
	int err1, err2;

#define  PCIE_MLW_CAP_SHIFT 4	/* start of MLW mask in link capabilities */

	*speed = PCI_SPEED_UNKNOWN;
	*width = PCIE_LNK_WIDTH_UNKNOWN;

	err1 = pcie_capability_read_dword(dev->persist->pdev, PCI_EXP_LNKCAP,
					  &lnkcap1);
	err2 = pcie_capability_read_dword(dev->persist->pdev, PCI_EXP_LNKCAP2,
					  &lnkcap2);
	if (!err2 && lnkcap2) { /* PCIe r3.0-compliant */
		if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_8_0GB)
			*speed = PCIE_SPEED_8_0GT;
		else if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_5_0GB)
			*speed = PCIE_SPEED_5_0GT;
		else if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_2_5GB)
			*speed = PCIE_SPEED_2_5GT;
	}
	if (!err1) {
		*width = (lnkcap1 & PCI_EXP_LNKCAP_MLW) >> PCIE_MLW_CAP_SHIFT;
		if (!lnkcap2) { /* pre-r3.0 */
			if (lnkcap1 & PCI_EXP_LNKCAP_SLS_5_0GB)
				*speed = PCIE_SPEED_5_0GT;
			else if (lnkcap1 & PCI_EXP_LNKCAP_SLS_2_5GB)
				*speed = PCIE_SPEED_2_5GT;
		}
	}

	if (*speed == PCI_SPEED_UNKNOWN || *width == PCIE_LNK_WIDTH_UNKNOWN) {
		return err1 ? err1 :
			err2 ? err2 : -EINVAL;
	}
	return 0;
}
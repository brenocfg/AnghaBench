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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct amd8111_pci_info {struct pci_dev* dev; } ;

/* Variables and functions */
 scalar_t__ EDAC_OPSTATE_POLL ; 
 int /*<<< orphan*/  HT_LINK_CRCFEN ; 
 int /*<<< orphan*/  PCI_INTBRG_CTRL_POLL_MASK ; 
 int /*<<< orphan*/  PCI_STSCMD_SERREN ; 
 int /*<<< orphan*/  REG_HT_LINK ; 
 int /*<<< orphan*/  REG_PCI_INTBRG_CTRL ; 
 int /*<<< orphan*/  REG_PCI_STSCMD ; 
 scalar_t__ edac_op_state ; 
 int /*<<< orphan*/  edac_pci_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_pci_write_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd8111_pci_bridge_exit(struct amd8111_pci_info *pci_info)
{
	u32 val32;
	struct pci_dev *dev = pci_info->dev;

	if (edac_op_state == EDAC_OPSTATE_POLL) {
		/* Disable System Error reporting */
		edac_pci_read_dword(dev, REG_PCI_STSCMD, &val32);
		val32 &= ~PCI_STSCMD_SERREN;
		edac_pci_write_dword(dev, REG_PCI_STSCMD, val32);

		/* Disable CRC flood packets */
		edac_pci_read_dword(dev, REG_HT_LINK, &val32);
		val32 &= ~HT_LINK_CRCFEN;
		edac_pci_write_dword(dev, REG_HT_LINK, val32);

		/* Disable DTSERREN/MARSP/SERREN in Interrupt Control reg */
		edac_pci_read_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
		val32 &= ~PCI_INTBRG_CTRL_POLL_MASK;
		edac_pci_write_dword(dev, REG_PCI_INTBRG_CTRL, val32);
	}
}
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
struct pci_dev {int dummy; } ;
struct amd8111_pci_info {struct pci_dev* dev; } ;

/* Variables and functions */
 scalar_t__ EDAC_OPSTATE_POLL ; 
 int HT_LINK_CLEAR_MASK ; 
 int HT_LINK_CRCFEN ; 
 int MEM_LIMIT_CLEAR_MASK ; 
 int PCI_INTBRG_CTRL_CLEAR_MASK ; 
 int PCI_INTBRG_CTRL_POLL_MASK ; 
 int PCI_STSCMD_CLEAR_MASK ; 
 int PCI_STSCMD_SERREN ; 
 int /*<<< orphan*/  REG_HT_LINK ; 
 int /*<<< orphan*/  REG_MEM_LIM ; 
 int /*<<< orphan*/  REG_PCI_INTBRG_CTRL ; 
 int /*<<< orphan*/  REG_PCI_STSCMD ; 
 scalar_t__ edac_op_state ; 
 int /*<<< orphan*/  edac_pci_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  edac_pci_write_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amd8111_pci_bridge_init(struct amd8111_pci_info *pci_info)
{
	u32 val32;
	struct pci_dev *dev = pci_info->dev;

	/* First clear error detection flags on the host interface */

	/* Clear SSE/SMA/STA flags in the global status register*/
	edac_pci_read_dword(dev, REG_PCI_STSCMD, &val32);
	if (val32 & PCI_STSCMD_CLEAR_MASK)
		edac_pci_write_dword(dev, REG_PCI_STSCMD, val32);

	/* Clear CRC and Link Fail flags in HT Link Control reg */
	edac_pci_read_dword(dev, REG_HT_LINK, &val32);
	if (val32 & HT_LINK_CLEAR_MASK)
		edac_pci_write_dword(dev, REG_HT_LINK, val32);

	/* Second clear all fault on the secondary interface */

	/* Clear error flags in the memory-base limit reg. */
	edac_pci_read_dword(dev, REG_MEM_LIM, &val32);
	if (val32 & MEM_LIMIT_CLEAR_MASK)
		edac_pci_write_dword(dev, REG_MEM_LIM, val32);

	/* Clear Discard Timer Expired flag in Interrupt/Bridge Control reg */
	edac_pci_read_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
	if (val32 & PCI_INTBRG_CTRL_CLEAR_MASK)
		edac_pci_write_dword(dev, REG_PCI_INTBRG_CTRL, val32);

	/* Last enable error detections */
	if (edac_op_state == EDAC_OPSTATE_POLL) {
		/* Enable System Error reporting in global status register */
		edac_pci_read_dword(dev, REG_PCI_STSCMD, &val32);
		val32 |= PCI_STSCMD_SERREN;
		edac_pci_write_dword(dev, REG_PCI_STSCMD, val32);

		/* Enable CRC Sync flood packets to HyperTransport Link */
		edac_pci_read_dword(dev, REG_HT_LINK, &val32);
		val32 |= HT_LINK_CRCFEN;
		edac_pci_write_dword(dev, REG_HT_LINK, val32);

		/* Enable SSE reporting etc in Interrupt control reg */
		edac_pci_read_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
		val32 |= PCI_INTBRG_CTRL_POLL_MASK;
		edac_pci_write_dword(dev, REG_PCI_INTBRG_CTRL, val32);
	}
}
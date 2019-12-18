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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int number; struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
#define  SNI_BRD_PCI_DESKTOP 132 
#define  SNI_BRD_PCI_MTOWER 131 
#define  SNI_BRD_PCI_MTOWER_CPLUS 130 
#define  SNI_BRD_PCI_TOWER 129 
#define  SNI_BRD_PCI_TOWER_CPLUS 128 
 int** irq_tab_pcit ; 
 int** irq_tab_pcit_cplus ; 
 int** irq_tab_rm200 ; 
 int** irq_tab_rm300d ; 
 int** irq_tab_rm300e ; 
 int /*<<< orphan*/  is_rm300_revd () ; 
 int sni_brd_type ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	switch (sni_brd_type) {
	case SNI_BRD_PCI_TOWER_CPLUS:
		if (slot == 4) {
			/*
			 * SNI messed up interrupt wiring for onboard
			 * PCI bus 1; we need to fix this up here
			 */
			while (dev && dev->bus->number != 1)
				dev = dev->bus->self;
			if (dev && dev->devfn >= PCI_DEVFN(4, 0))
				slot = 5;
		}
		return irq_tab_pcit_cplus[slot][pin];
	case SNI_BRD_PCI_TOWER:
		return irq_tab_pcit[slot][pin];

	case SNI_BRD_PCI_MTOWER:
		if (is_rm300_revd())
			return irq_tab_rm300d[slot][pin];
		/* fall through */

	case SNI_BRD_PCI_DESKTOP:
		return irq_tab_rm200[slot][pin];

	case SNI_BRD_PCI_MTOWER_CPLUS:
		return irq_tab_rm300e[slot][pin];
	}

	return 0;
}
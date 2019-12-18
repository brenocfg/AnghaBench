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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_BIST ; 
 unsigned char PCI_BIST_CAPABLE ; 
 unsigned char PCI_BIST_CODE_MASK ; 
 unsigned char PCI_BIST_START ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int jiffies ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static void final_fixup(struct pci_dev *dev)
{
	unsigned char bist;

	/* Do build-in self test */
	if (pci_read_config_byte(dev, PCI_BIST, &bist) == PCIBIOS_SUCCESSFUL &&
	    (bist & PCI_BIST_CAPABLE)) {
		unsigned long timeout;
		pci_set_power_state(dev, PCI_D0);
		pr_info("PCI: %s BIST...", pci_name(dev));
		pci_write_config_byte(dev, PCI_BIST, PCI_BIST_START);
		timeout = jiffies + HZ * 2;	/* timeout after 2 sec */
		do {
			pci_read_config_byte(dev, PCI_BIST, &bist);
			if (time_after(jiffies, timeout))
				break;
		} while (bist & PCI_BIST_START);
		if (bist & (PCI_BIST_CODE_MASK | PCI_BIST_START))
			pr_cont("failed. (0x%x)\n", bist);
		else
			pr_cont("OK.\n");
	}
}
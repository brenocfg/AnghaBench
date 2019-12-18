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
typedef  int /*<<< orphan*/  u16 ;
struct resource {int flags; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_IO ; 
 int /*<<< orphan*/  PCI_COMMAND_MEMORY ; 
 int PCI_NUM_RESOURCES ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcibios_enable_device(struct pci_dev *dev, int mask)
{
	u16 cmd, oldcmd;
	int i;

	pci_read_config_word(dev, PCI_COMMAND, &cmd);
	oldcmd = cmd;

	for (i = 0; i < PCI_NUM_RESOURCES; i++) {
		struct resource *res = &dev->resource[i];

		/* Only set up the requested stuff */
		if (!(mask & (1<<i)))
			continue;

		if (res->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		if (res->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	}

	if (cmd != oldcmd) {
		pci_info(dev, "enabling device (%04x -> %04x)\n", oldcmd, cmd);
		pci_write_config_word(dev, PCI_COMMAND, cmd);
	}
	return 0;
}
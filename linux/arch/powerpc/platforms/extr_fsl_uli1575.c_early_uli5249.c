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
struct pci_dev {int class; } ;

/* Variables and functions */
 int PCI_CLASS_PROG ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  is_quirk_valid () ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void early_uli5249(struct pci_dev *dev)
{
	unsigned char temp;

	if (!is_quirk_valid())
		return;

	pci_write_config_word(dev, PCI_COMMAND, PCI_COMMAND_IO |
		 PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);

	/* read/write lock */
	pci_read_config_byte(dev, 0x7c, &temp);
	pci_write_config_byte(dev, 0x7c, 0x80);

	/* set as P2P bridge */
	pci_write_config_byte(dev, PCI_CLASS_PROG, 0x01);
	dev->class |= 0x1;

	/* restore lock */
	pci_write_config_byte(dev, 0x7c, temp);
}
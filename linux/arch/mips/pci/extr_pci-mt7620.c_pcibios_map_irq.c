#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct pci_dev {int irq; TYPE_1__* bus; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int RALINK_INT_PCIE0 ; 
 int /*<<< orphan*/  RALINK_PCI0_BAR0SETUP_ADDR ; 
 int /*<<< orphan*/  RALINK_PCI_MEMORY_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  pci_config_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_config_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_w32 (int,int /*<<< orphan*/ ) ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	u16 cmd;
	u32 val;
	int irq = 0;

	if ((dev->bus->number == 0) && (slot == 0)) {
		pcie_w32(0x7FFF0001, RALINK_PCI0_BAR0SETUP_ADDR);
		pci_config_write(dev->bus, 0, PCI_BASE_ADDRESS_0, 4,
				 RALINK_PCI_MEMORY_BASE);
		pci_config_read(dev->bus, 0, PCI_BASE_ADDRESS_0, 4, &val);
	} else if ((dev->bus->number == 1) && (slot == 0x0)) {
		irq = RALINK_INT_PCIE0;
	} else {
		dev_err(&dev->dev, "no irq found - bus=0x%x, slot = 0x%x\n",
			dev->bus->number, slot);
		return 0;
	}
	dev_err(&dev->dev, "card - bus=0x%x, slot = 0x%x irq=%d\n",
		dev->bus->number, slot, irq);

	/* configure the cache line size to 0x14 */
	pci_write_config_byte(dev, PCI_CACHE_LINE_SIZE, 0x14);

	/* configure latency timer to 0xff */
	pci_write_config_byte(dev, PCI_LATENCY_TIMER, 0xff);
	pci_read_config_word(dev, PCI_COMMAND, &cmd);

	/* setup the slot */
	cmd = cmd | PCI_COMMAND_MASTER | PCI_COMMAND_IO | PCI_COMMAND_MEMORY;
	pci_write_config_word(dev, PCI_COMMAND, cmd);
	pci_write_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);

	return irq;
}
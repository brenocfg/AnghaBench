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

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_CONF_ADDR ; 
 int PCI_CONF_ADDR_EN ; 
 int PCI_CONF_BUS (int) ; 
 int /*<<< orphan*/  PCI_CONF_DATA ; 
 int PCI_CONF_DEV (int) ; 
 int PCI_CONF_FUNC (int) ; 
 int PCI_CONF_REG (int) ; 
 int /*<<< orphan*/  orion5x_pci_lock ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orion5x_pci_hw_rd_conf(int bus, int dev, u32 func,
					u32 where, u32 size, u32 *val)
{
	unsigned long flags;
	spin_lock_irqsave(&orion5x_pci_lock, flags);

	writel(PCI_CONF_BUS(bus) |
		PCI_CONF_DEV(dev) | PCI_CONF_REG(where) |
		PCI_CONF_FUNC(func) | PCI_CONF_ADDR_EN, PCI_CONF_ADDR);

	*val = readl(PCI_CONF_DATA);

	if (size == 1)
		*val = (*val >> (8*(where & 0x3))) & 0xff;
	else if (size == 2)
		*val = (*val >> (8*(where & 0x3))) & 0xffff;

	spin_unlock_irqrestore(&orion5x_pci_lock, flags);

	return PCIBIOS_SUCCESSFUL;
}
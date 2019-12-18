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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_PCI_GPIO_OUT ; 
 int /*<<< orphan*/  BHNDB_PCI_GPIO_OUTEN ; 
 int BHNDB_PCI_GPIO_PLL_OFF ; 
 int BHNDB_PCI_GPIO_XTAL_ON ; 
 scalar_t__ bhndb_is_pcie_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
bhndb_disable_pci_clocks(device_t dev)
{
	device_t	pci_dev;
	uint32_t	gpio_out, gpio_en;

	pci_dev = device_get_parent(dev);

	/* Only supported and required on PCI devices */
	if (bhndb_is_pcie_attached(dev))
		return (0);

	/* Fetch current config */
	gpio_out = pci_read_config(pci_dev, BHNDB_PCI_GPIO_OUT, 4);
	gpio_en = pci_read_config(pci_dev, BHNDB_PCI_GPIO_OUTEN, 4);

	/* Set PLL_OFF to HIGH, XTAL_ON to LOW. */
	gpio_out &= ~BHNDB_PCI_GPIO_XTAL_ON;
	gpio_out |= BHNDB_PCI_GPIO_PLL_OFF;
	pci_write_config(pci_dev, BHNDB_PCI_GPIO_OUT, gpio_out, 4);

	/* Enable both output pins */
	gpio_en |= (BHNDB_PCI_GPIO_PLL_OFF|BHNDB_PCI_GPIO_XTAL_ON);
	pci_write_config(pci_dev, BHNDB_PCI_GPIO_OUTEN, gpio_en, 4);

	return (0);
}
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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_PCI_GPIO_IN ; 
 int /*<<< orphan*/  BHNDB_PCI_GPIO_OUT ; 
 int /*<<< orphan*/  BHNDB_PCI_GPIO_OUTEN ; 
 int BHNDB_PCI_GPIO_PLL_OFF ; 
 int BHNDB_PCI_GPIO_XTAL_ON ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PCIM_STATUS_STABORT ; 
 int /*<<< orphan*/  PCIR_STATUS ; 
 scalar_t__ bhndb_is_pcie_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
bhndb_enable_pci_clocks(device_t dev)
{
	device_t		pci_dev;
	uint32_t		gpio_in, gpio_out, gpio_en;
	uint32_t		gpio_flags;
	uint16_t		pci_status;

	pci_dev = device_get_parent(dev);

	/* Only supported and required on PCI devices */
	if (bhndb_is_pcie_attached(dev))
		return (0);

	/* Read state of XTAL pin */
	gpio_in = pci_read_config(pci_dev, BHNDB_PCI_GPIO_IN, 4);
	if (gpio_in & BHNDB_PCI_GPIO_XTAL_ON)
		return (0); /* already enabled */

	/* Fetch current config */
	gpio_out = pci_read_config(pci_dev, BHNDB_PCI_GPIO_OUT, 4);
	gpio_en = pci_read_config(pci_dev, BHNDB_PCI_GPIO_OUTEN, 4);

	/* Set PLL_OFF/XTAL_ON pins to HIGH and enable both pins */
	gpio_flags = (BHNDB_PCI_GPIO_PLL_OFF|BHNDB_PCI_GPIO_XTAL_ON);
	gpio_out |= gpio_flags;
	gpio_en |= gpio_flags;

	pci_write_config(pci_dev, BHNDB_PCI_GPIO_OUT, gpio_out, 4);
	pci_write_config(pci_dev, BHNDB_PCI_GPIO_OUTEN, gpio_en, 4);
	DELAY(1000);

	/* Reset PLL_OFF */
	gpio_out &= ~BHNDB_PCI_GPIO_PLL_OFF;
	pci_write_config(pci_dev, BHNDB_PCI_GPIO_OUT, gpio_out, 4);
	DELAY(5000);

	/* Clear any PCI 'sent target-abort' flag. */
	pci_status = pci_read_config(pci_dev, PCIR_STATUS, 2);
	pci_status &= ~PCIM_STATUS_STABORT;
	pci_write_config(pci_dev, PCIR_STATUS, pci_status, 2);

	return (0);
}
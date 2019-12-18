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
struct oxnas_pcie {struct oxnas_pcie** private_data; } ;
struct hw_pci {int nr_controllers; int /*<<< orphan*/ * ops; int /*<<< orphan*/  map_irq; int /*<<< orphan*/  setup; struct oxnas_pcie** private_data; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  hw ;

/* Variables and functions */
 int NUM_CONTROLLERS ; 
 int /*<<< orphan*/  memset (struct hw_pci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_irq_parse_and_map_pci ; 
 int /*<<< orphan*/  oxnas_pcie_ops ; 
 int /*<<< orphan*/  oxnas_pcie_setup ; 
 int /*<<< orphan*/  pci_common_init_dev (struct device*,struct hw_pci*) ; 

__attribute__((used)) static void oxnas_pcie_enable(struct device *dev, struct oxnas_pcie *pcie)
{
	struct hw_pci hw;
	int i;

	memset(&hw, 0, sizeof(hw));
	for (i = 0; i < NUM_CONTROLLERS; i++)
		pcie->private_data[i] = pcie;

	hw.nr_controllers = NUM_CONTROLLERS;
/* I think use stack pointer is a bad idea though it is valid in this case */
	hw.private_data   = pcie->private_data;
	hw.setup          = oxnas_pcie_setup;
	hw.map_irq        = of_irq_parse_and_map_pci;
	hw.ops            = &oxnas_pcie_ops;

	/* pass dev to maintain of tree, interrupt mapping rely on this */
	pci_common_init_dev(dev, &hw);
}
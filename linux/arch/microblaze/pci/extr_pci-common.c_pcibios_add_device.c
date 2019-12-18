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
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_irq_parse_and_map_pci (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcibios_add_device(struct pci_dev *dev)
{
	dev->irq = of_irq_parse_and_map_pci(dev, 0, 0);

	return 0;
}
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
typedef  int u8 ;
struct pci_dev {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int nr_legacy_irqs () ; 
 int pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int xen_bind_pirq_gsi_to_irq (int,int,int,char*) ; 

__attribute__((used)) static int xen_pcifront_enable_irq(struct pci_dev *dev)
{
	int rc;
	int share = 1;
	int pirq;
	u8 gsi;

	rc = pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &gsi);
	if (rc < 0) {
		dev_warn(&dev->dev, "Xen PCI: failed to read interrupt line: %d\n",
			 rc);
		return rc;
	}
	/* In PV DomU the Xen PCI backend puts the PIRQ in the interrupt line.*/
	pirq = gsi;

	if (gsi < nr_legacy_irqs())
		share = 0;

	rc = xen_bind_pirq_gsi_to_irq(gsi, pirq, share, "pcifront");
	if (rc < 0) {
		dev_warn(&dev->dev, "Xen PCI: failed to bind GSI%d (PIRQ%d) to IRQ: %d\n",
			 gsi, pirq, rc);
		return rc;
	}

	dev->irq = rc;
	dev_info(&dev->dev, "Xen PCI mapped GSI%d to IRQ%d\n", gsi, dev->irq);
	return 0;
}
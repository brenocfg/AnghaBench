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
struct safexcel_ring_irq_data {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pci_dev {struct device dev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  CONFIG_PCI ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ring_irq_data*) ; 
 int pci_irq_vector (struct pci_dev*,int) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int safexcel_request_ring_irq(void *pdev, int irqid,
				     int is_pci_dev,
				     irq_handler_t handler,
				     irq_handler_t threaded_handler,
				     struct safexcel_ring_irq_data *ring_irq_priv)
{
	int ret, irq;
	struct device *dev;

	if (IS_ENABLED(CONFIG_PCI) && is_pci_dev) {
		struct pci_dev *pci_pdev = pdev;

		dev = &pci_pdev->dev;
		irq = pci_irq_vector(pci_pdev, irqid);
		if (irq < 0) {
			dev_err(dev, "unable to get device MSI IRQ %d (err %d)\n",
				irqid, irq);
			return irq;
		}
	} else if (IS_ENABLED(CONFIG_OF)) {
		struct platform_device *plf_pdev = pdev;
		char irq_name[6] = {0}; /* "ringX\0" */

		snprintf(irq_name, 6, "ring%d", irqid);
		dev = &plf_pdev->dev;
		irq = platform_get_irq_byname(plf_pdev, irq_name);

		if (irq < 0) {
			dev_err(dev, "unable to get IRQ '%s' (err %d)\n",
				irq_name, irq);
			return irq;
		}
	}

	ret = devm_request_threaded_irq(dev, irq, handler,
					threaded_handler, IRQF_ONESHOT,
					dev_name(dev), ring_irq_priv);
	if (ret) {
		dev_err(dev, "unable to request IRQ %d\n", irq);
		return ret;
	}

	return irq;
}
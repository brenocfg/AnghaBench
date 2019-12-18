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
struct pci_dev {int dummy; } ;
struct hifn_dma {int dummy; } ;
struct hifn_device {scalar_t__* bar; int /*<<< orphan*/  desc_dma; int /*<<< orphan*/  desc_virt; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_flush (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_reset_dma (struct hifn_device*,int) ; 
 int /*<<< orphan*/  hifn_stop_device (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_unregister_alg (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_unregister_rng (struct hifn_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct hifn_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hifn_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hifn_remove(struct pci_dev *pdev)
{
	int i;
	struct hifn_device *dev;

	dev = pci_get_drvdata(pdev);

	if (dev) {
		cancel_delayed_work_sync(&dev->work);

		hifn_unregister_rng(dev);
		hifn_unregister_alg(dev);
		hifn_reset_dma(dev, 1);
		hifn_stop_device(dev);

		free_irq(dev->irq, dev);
		tasklet_kill(&dev->tasklet);

		hifn_flush(dev);

		pci_free_consistent(pdev, sizeof(struct hifn_dma),
				dev->desc_virt, dev->desc_dma);
		for (i = 0; i < 3; ++i)
			if (dev->bar[i])
				iounmap(dev->bar[i]);

		kfree(dev);
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);
}
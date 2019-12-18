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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; int /*<<< orphan*/  dev; } ;
struct dw_dma_chip_pdata {int (* probe ) (struct dw_dma_chip*) ;struct dw_dma_chip* chip; int /*<<< orphan*/  pdata; } ;
struct dw_dma_chip {int /*<<< orphan*/  pdata; int /*<<< orphan*/  irq; int /*<<< orphan*/  regs; int /*<<< orphan*/  id; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct dw_dma_chip_pdata* devm_kmemdup (int /*<<< orphan*/ *,struct dw_dma_chip_pdata const*,int,int /*<<< orphan*/ ) ; 
 struct dw_dma_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct dw_dma_chip_pdata*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int stub1 (struct dw_dma_chip*) ; 

__attribute__((used)) static int dw_pci_probe(struct pci_dev *pdev, const struct pci_device_id *pid)
{
	const struct dw_dma_chip_pdata *drv_data = (void *)pid->driver_data;
	struct dw_dma_chip_pdata *data;
	struct dw_dma_chip *chip;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	ret = pcim_iomap_regions(pdev, 1 << 0, pci_name(pdev));
	if (ret) {
		dev_err(&pdev->dev, "I/O memory remapping failed\n");
		return ret;
	}

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	data = devm_kmemdup(&pdev->dev, drv_data, sizeof(*drv_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->dev = &pdev->dev;
	chip->id = pdev->devfn;
	chip->regs = pcim_iomap_table(pdev)[0];
	chip->irq = pdev->irq;
	chip->pdata = data->pdata;

	data->chip = chip;

	ret = data->probe(chip);
	if (ret)
		return ret;

	pci_set_drvdata(pdev, data);

	return 0;
}
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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct dw_dma_chip_pdata {int (* remove ) (struct dw_dma_chip*) ;struct dw_dma_chip* chip; } ;
struct dw_dma_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct dw_dma_chip_pdata* pci_get_drvdata (struct pci_dev*) ; 
 int stub1 (struct dw_dma_chip*) ; 

__attribute__((used)) static void dw_pci_remove(struct pci_dev *pdev)
{
	struct dw_dma_chip_pdata *data = pci_get_drvdata(pdev);
	struct dw_dma_chip *chip = data->chip;
	int ret;

	ret = data->remove(chip);
	if (ret)
		dev_warn(&pdev->dev, "can't remove device properly: %d\n", ret);
}
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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_edma_engine {scalar_t__ txirq; scalar_t__ errirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct fsl_edma_engine*) ; 
 int /*<<< orphan*/  fsl_edma_err_handler ; 
 int /*<<< orphan*/  fsl_edma_irq_handler ; 
 int /*<<< orphan*/  fsl_edma_tx_handler ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 

__attribute__((used)) static int
fsl_edma_irq_init(struct platform_device *pdev, struct fsl_edma_engine *fsl_edma)
{
	int ret;

	fsl_edma->txirq = platform_get_irq_byname(pdev, "edma-tx");
	if (fsl_edma->txirq < 0)
		return fsl_edma->txirq;

	fsl_edma->errirq = platform_get_irq_byname(pdev, "edma-err");
	if (fsl_edma->errirq < 0)
		return fsl_edma->errirq;

	if (fsl_edma->txirq == fsl_edma->errirq) {
		ret = devm_request_irq(&pdev->dev, fsl_edma->txirq,
				fsl_edma_irq_handler, 0, "eDMA", fsl_edma);
		if (ret) {
			dev_err(&pdev->dev, "Can't register eDMA IRQ.\n");
			return ret;
		}
	} else {
		ret = devm_request_irq(&pdev->dev, fsl_edma->txirq,
				fsl_edma_tx_handler, 0, "eDMA tx", fsl_edma);
		if (ret) {
			dev_err(&pdev->dev, "Can't register eDMA tx IRQ.\n");
			return ret;
		}

		ret = devm_request_irq(&pdev->dev, fsl_edma->errirq,
				fsl_edma_err_handler, 0, "eDMA err", fsl_edma);
		if (ret) {
			dev_err(&pdev->dev, "Can't register eDMA err IRQ.\n");
			return ret;
		}
	}

	return 0;
}
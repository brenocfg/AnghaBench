#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct fsl_qdma_queue {int n_cq; int /*<<< orphan*/  bus_addr; int /*<<< orphan*/  cq; } ;
struct fsl_qdma_format {int dummy; } ;
struct fsl_qdma_engine {int block_number; struct fsl_qdma_queue** status; int /*<<< orphan*/  dma_dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_qdma_cleanup_vchan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_qdma_irq_exit (struct platform_device*,struct fsl_qdma_engine*) ; 
 int /*<<< orphan*/  of_dma_controller_free (struct device_node*) ; 
 struct fsl_qdma_engine* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsl_qdma_remove(struct platform_device *pdev)
{
	int i;
	struct fsl_qdma_queue *status;
	struct device_node *np = pdev->dev.of_node;
	struct fsl_qdma_engine *fsl_qdma = platform_get_drvdata(pdev);

	fsl_qdma_irq_exit(pdev, fsl_qdma);
	fsl_qdma_cleanup_vchan(&fsl_qdma->dma_dev);
	of_dma_controller_free(np);
	dma_async_device_unregister(&fsl_qdma->dma_dev);

	for (i = 0; i < fsl_qdma->block_number; i++) {
		status = fsl_qdma->status[i];
		dma_free_coherent(&pdev->dev, sizeof(struct fsl_qdma_format) *
				status->n_cq, status->cq, status->bus_addr);
	}
	return 0;
}
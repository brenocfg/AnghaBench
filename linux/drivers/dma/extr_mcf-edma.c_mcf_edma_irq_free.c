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
struct resource {int start; int end; } ;
struct platform_device {int dummy; } ;
struct fsl_edma_engine {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  free_irq (int,struct fsl_edma_engine*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mcf_edma_irq_free(struct platform_device *pdev,
				struct fsl_edma_engine *mcf_edma)
{
	int irq;
	struct resource *res;

	res = platform_get_resource_byname(pdev,
			IORESOURCE_IRQ, "edma-tx-00-15");
	if (res) {
		for (irq = res->start; irq <= res->end; irq++)
			free_irq(irq, mcf_edma);
	}

	res = platform_get_resource_byname(pdev,
			IORESOURCE_IRQ, "edma-tx-16-55");
	if (res) {
		for (irq = res->start; irq <= res->end; irq++)
			free_irq(irq, mcf_edma);
	}

	irq = platform_get_irq_byname(pdev, "edma-tx-56-63");
	if (irq != -ENXIO)
		free_irq(irq, mcf_edma);

	irq = platform_get_irq_byname(pdev, "edma-err");
	if (irq != -ENXIO)
		free_irq(irq, mcf_edma);
}
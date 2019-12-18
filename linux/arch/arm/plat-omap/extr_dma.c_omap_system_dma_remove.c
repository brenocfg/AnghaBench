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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int dma_chan_count ; 
 scalar_t__ dma_omap2plus () ; 
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int /*<<< orphan*/  omap24xx_dma_irq ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  remove_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int omap_system_dma_remove(struct platform_device *pdev)
{
	int dma_irq;

	if (dma_omap2plus()) {
		char irq_name[4];
		strcpy(irq_name, "0");
		dma_irq = platform_get_irq_byname(pdev, irq_name);
		if (dma_irq >= 0)
			remove_irq(dma_irq, &omap24xx_dma_irq);
	} else {
		int irq_rel = 0;
		for ( ; irq_rel < dma_chan_count; irq_rel++) {
			dma_irq = platform_get_irq(pdev, irq_rel);
			free_irq(dma_irq, (void *)(irq_rel + 1));
		}
	}
	return 0;
}
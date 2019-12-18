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
struct TYPE_2__ {void** dma_mask; void* coherent_dma_mask; } ;
struct platform_device {void* dma_mask; TYPE_1__ dev; } ;

/* Variables and functions */
 void* DMA_BIT_MASK (int) ; 

__attribute__((used)) static void setup_pdev_dma_masks(struct platform_device *pdev)
{
	if (!pdev->dev.coherent_dma_mask)
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	if (!pdev->dma_mask)
		pdev->dma_mask = DMA_BIT_MASK(32);
	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dma_mask;
}
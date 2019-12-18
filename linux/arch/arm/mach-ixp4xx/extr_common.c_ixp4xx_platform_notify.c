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
struct device {void* coherent_dma_mask; void** dma_mask; } ;

/* Variables and functions */
 void* DMA_BIT_MASK (int) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dmabounce_register_dev (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp4xx_needs_bounce ; 

__attribute__((used)) static int ixp4xx_platform_notify(struct device *dev)
{
	dev->dma_mask = &dev->coherent_dma_mask;

#ifdef CONFIG_PCI
	if (dev_is_pci(dev)) {
		dev->coherent_dma_mask = DMA_BIT_MASK(28); /* 64 MB */
		dmabounce_register_dev(dev, 2048, 4096, ixp4xx_needs_bounce);
		return 0;
	}
#endif

	dev->coherent_dma_mask = DMA_BIT_MASK(32);
	return 0;
}
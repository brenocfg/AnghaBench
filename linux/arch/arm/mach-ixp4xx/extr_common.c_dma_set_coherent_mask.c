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
typedef  int u64 ;
struct device {int coherent_dma_mask; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int EIO ; 
 scalar_t__ dev_is_pci (struct device*) ; 

int dma_set_coherent_mask(struct device *dev, u64 mask)
{
	if (dev_is_pci(dev))
		mask &= DMA_BIT_MASK(28); /* 64 MB */

	if ((mask & DMA_BIT_MASK(28)) == DMA_BIT_MASK(28)) {
		dev->coherent_dma_mask = mask;
		return 0;
	}

	return -EIO;		/* device wanted sub-64MB mask */
}
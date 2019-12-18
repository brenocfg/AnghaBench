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
typedef  scalar_t__ u64 ;
struct device {scalar_t__ coherent_dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  __dma_supported (struct device*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static u64 get_coherent_dma_mask(struct device *dev)
{
	u64 mask = (u64)DMA_BIT_MASK(32);

	if (dev) {
		mask = dev->coherent_dma_mask;

		/*
		 * Sanity check the DMA mask - it must be non-zero, and
		 * must be able to be satisfied by a DMA allocation.
		 */
		if (mask == 0) {
			dev_warn(dev, "coherent DMA mask is unset\n");
			return 0;
		}

		if (!__dma_supported(dev, mask, true))
			return 0;
	}

	return mask;
}
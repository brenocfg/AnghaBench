#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dmabounce; } ;
struct device {unsigned long* dma_mask; TYPE_2__ archdata; } ;
typedef  size_t dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* needs_bounce ) (struct device*,size_t,size_t) ;} ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct device*,size_t,size_t) ; 

__attribute__((used)) static int needs_bounce(struct device *dev, dma_addr_t dma_addr, size_t size)
{
	if (!dev || !dev->archdata.dmabounce)
		return 0;

	if (dev->dma_mask) {
		unsigned long limit, mask = *dev->dma_mask;

		limit = (mask + 1) & ~mask;
		if (limit && size > limit) {
			dev_err(dev, "DMA mapping too big (requested %#x "
				"mask %#Lx)\n", size, *dev->dma_mask);
			return -E2BIG;
		}

		/* Figure out if we need to bounce from the DMA mask. */
		if ((dma_addr | (dma_addr + size - 1)) & ~mask)
			return 1;
	}

	return !!dev->archdata.dmabounce->needs_bounce(dev, dma_addr, size);
}
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
struct device {int dummy; } ;
struct cpuinfo_or1k {unsigned long dcache_block_size; } ;
typedef  unsigned long phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  SPR_DCBFR ; 
 int /*<<< orphan*/  SPR_DCBIR ; 
 struct cpuinfo_or1k* cpuinfo_or1k ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 size_t smp_processor_id () ; 

void arch_sync_dma_for_device(struct device *dev, phys_addr_t addr, size_t size,
		enum dma_data_direction dir)
{
	unsigned long cl;
	struct cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[smp_processor_id()];

	switch (dir) {
	case DMA_TO_DEVICE:
		/* Flush the dcache for the requested range */
		for (cl = addr; cl < addr + size;
		     cl += cpuinfo->dcache_block_size)
			mtspr(SPR_DCBFR, cl);
		break;
	case DMA_FROM_DEVICE:
		/* Invalidate the dcache for the requested range */
		for (cl = addr; cl < addr + size;
		     cl += cpuinfo->dcache_block_size)
			mtspr(SPR_DCBIR, cl);
		break;
	default:
		/*
		 * NOTE: If dir == DMA_BIDIRECTIONAL then there's no need to
		 * flush nor invalidate the cache here as the area will need
		 * to be manually synced anyway.
		 */
		break;
	}
}
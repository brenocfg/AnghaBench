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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  __flush_invalidate_region (void*,size_t) ; 
 int /*<<< orphan*/  __flush_purge_region (void*,size_t) ; 
 int /*<<< orphan*/  __flush_wback_region (void*,size_t) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 void* sh_cacheop_vaddr (int /*<<< orphan*/ ) ; 

void arch_sync_dma_for_device(struct device *dev, phys_addr_t paddr,
		size_t size, enum dma_data_direction dir)
{
	void *addr = sh_cacheop_vaddr(phys_to_virt(paddr));

	switch (dir) {
	case DMA_FROM_DEVICE:		/* invalidate only */
		__flush_invalidate_region(addr, size);
		break;
	case DMA_TO_DEVICE:		/* writeback only */
		__flush_wback_region(addr, size);
		break;
	case DMA_BIDIRECTIONAL:		/* writeback and invalidate */
		__flush_purge_region(addr, size);
		break;
	default:
		BUG();
	}
}
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
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  cache_clear (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cache_push (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int) ; 

void arch_sync_dma_for_device(struct device *dev, phys_addr_t handle,
		size_t size, enum dma_data_direction dir)
{
	switch (dir) {
	case DMA_BIDIRECTIONAL:
	case DMA_TO_DEVICE:
		cache_push(handle, size);
		break;
	case DMA_FROM_DEVICE:
		cache_clear(handle, size);
		break;
	default:
		pr_err_ratelimited("dma_sync_single_for_device: unsupported dir %u\n",
				   dir);
		break;
	}
}
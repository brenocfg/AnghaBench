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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  arch_sync_dma_for_cpu (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  vdma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdma_log2phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jazz_dma_unmap_page(struct device *dev, dma_addr_t dma_addr,
		size_t size, enum dma_data_direction dir, unsigned long attrs)
{
	if (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_for_cpu(dev, vdma_log2phys(dma_addr), size, dir);
	vdma_free(dma_addr);
}
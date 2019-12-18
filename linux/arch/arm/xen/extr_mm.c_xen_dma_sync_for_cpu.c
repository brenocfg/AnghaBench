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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GNTTAB_CACHE_INVAL ; 
 int /*<<< orphan*/  PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_sync_dma_for_cpu (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  dma_cache_maint (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_valid (int /*<<< orphan*/ ) ; 

void xen_dma_sync_for_cpu(struct device *dev, dma_addr_t handle,
		phys_addr_t paddr, size_t size, enum dma_data_direction dir)
{
	if (pfn_valid(PFN_DOWN(handle)))
		arch_sync_dma_for_cpu(dev, paddr, size, dir);
	else if (dir != DMA_TO_DEVICE)
		dma_cache_maint(handle, size, GNTTAB_CACHE_INVAL);
}
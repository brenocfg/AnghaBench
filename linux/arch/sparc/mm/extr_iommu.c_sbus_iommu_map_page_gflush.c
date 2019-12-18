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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __sbus_iommu_map_page (struct device*,struct page*,unsigned long,size_t,int) ; 
 int /*<<< orphan*/  flush_page_for_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_addr_t sbus_iommu_map_page_gflush(struct device *dev,
		struct page *page, unsigned long offset, size_t len,
		enum dma_data_direction dir, unsigned long attrs)
{
	flush_page_for_dma(0);
	return __sbus_iommu_map_page(dev, page, offset, len, false);
}
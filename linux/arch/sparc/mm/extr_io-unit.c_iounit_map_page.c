#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct iounit_struct {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct iounit_struct* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_MAPPING_ERROR ; 
 unsigned long iounit_get_area (struct iounit_struct*,unsigned long,size_t) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static dma_addr_t iounit_map_page(struct device *dev, struct page *page,
		unsigned long offset, size_t len, enum dma_data_direction dir,
		unsigned long attrs)
{
	void *vaddr = page_address(page) + offset;
	struct iounit_struct *iounit = dev->archdata.iommu;
	unsigned long ret, flags;
	
	/* XXX So what is maxphys for us and how do drivers know it? */
	if (!len || len > 256 * 1024)
		return DMA_MAPPING_ERROR;

	spin_lock_irqsave(&iounit->lock, flags);
	ret = iounit_get_area(iounit, (unsigned long)vaddr, len);
	spin_unlock_irqrestore(&iounit->lock, flags);
	return ret;
}
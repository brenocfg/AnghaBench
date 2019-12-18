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
struct iommu_table {unsigned long it_size; unsigned long it_hint; int /*<<< orphan*/  it_lock; int /*<<< orphan*/  it_map; TYPE_1__* chip_ops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tce_cache_blast ) (struct iommu_table*) ;} ;

/* Variables and functions */
 unsigned long ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long DMA_MAPPING_ERROR ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ dma_get_seg_boundary (struct device*) ; 
 unsigned long iommu_area_alloc (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_overflow ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct iommu_table*) ; 

__attribute__((used)) static unsigned long iommu_range_alloc(struct device *dev,
				       struct iommu_table *tbl,
				       unsigned int npages)
{
	unsigned long flags;
	unsigned long offset;
	unsigned long boundary_size;

	boundary_size = ALIGN(dma_get_seg_boundary(dev) + 1,
			      PAGE_SIZE) >> PAGE_SHIFT;

	BUG_ON(npages == 0);

	spin_lock_irqsave(&tbl->it_lock, flags);

	offset = iommu_area_alloc(tbl->it_map, tbl->it_size, tbl->it_hint,
				  npages, 0, boundary_size, 0);
	if (offset == ~0UL) {
		tbl->chip_ops->tce_cache_blast(tbl);

		offset = iommu_area_alloc(tbl->it_map, tbl->it_size, 0,
					  npages, 0, boundary_size, 0);
		if (offset == ~0UL) {
			pr_warn("IOMMU full\n");
			spin_unlock_irqrestore(&tbl->it_lock, flags);
			if (panic_on_overflow)
				panic("Calgary: fix the allocator.\n");
			else
				return DMA_MAPPING_ERROR;
		}
	}

	tbl->it_hint = offset + npages;
	BUG_ON(tbl->it_hint > tbl->it_size);

	spin_unlock_irqrestore(&tbl->it_lock, flags);

	return offset;
}
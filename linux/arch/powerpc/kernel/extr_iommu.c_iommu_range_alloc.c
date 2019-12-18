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
struct iommu_pool {unsigned long start; unsigned long end; unsigned long hint; int /*<<< orphan*/  lock; } ;
struct iommu_table {int nr_pools; unsigned long it_offset; int it_page_shift; unsigned long it_blocksize; struct iommu_pool* pools; int /*<<< orphan*/  it_map; struct iommu_pool large_pool; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 unsigned long DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long dma_get_seg_boundary (struct device*) ; 
 unsigned long iommu_area_alloc (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iommu_pool_hash ; 
 scalar_t__ likely (int) ; 
 scalar_t__ printk_ratelimit () ; 
 int raw_cpu_read (int /*<<< orphan*/ ) ; 
 scalar_t__ should_fail_iommu (struct device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long iommu_range_alloc(struct device *dev,
				       struct iommu_table *tbl,
                                       unsigned long npages,
                                       unsigned long *handle,
                                       unsigned long mask,
                                       unsigned int align_order)
{ 
	unsigned long n, end, start;
	unsigned long limit;
	int largealloc = npages > 15;
	int pass = 0;
	unsigned long align_mask;
	unsigned long boundary_size;
	unsigned long flags;
	unsigned int pool_nr;
	struct iommu_pool *pool;

	align_mask = (1ull << align_order) - 1;

	/* This allocator was derived from x86_64's bit string search */

	/* Sanity check */
	if (unlikely(npages == 0)) {
		if (printk_ratelimit())
			WARN_ON(1);
		return DMA_MAPPING_ERROR;
	}

	if (should_fail_iommu(dev))
		return DMA_MAPPING_ERROR;

	/*
	 * We don't need to disable preemption here because any CPU can
	 * safely use any IOMMU pool.
	 */
	pool_nr = raw_cpu_read(iommu_pool_hash) & (tbl->nr_pools - 1);

	if (largealloc)
		pool = &(tbl->large_pool);
	else
		pool = &(tbl->pools[pool_nr]);

	spin_lock_irqsave(&(pool->lock), flags);

again:
	if ((pass == 0) && handle && *handle &&
	    (*handle >= pool->start) && (*handle < pool->end))
		start = *handle;
	else
		start = pool->hint;

	limit = pool->end;

	/* The case below can happen if we have a small segment appended
	 * to a large, or when the previous alloc was at the very end of
	 * the available space. If so, go back to the initial start.
	 */
	if (start >= limit)
		start = pool->start;

	if (limit + tbl->it_offset > mask) {
		limit = mask - tbl->it_offset + 1;
		/* If we're constrained on address range, first try
		 * at the masked hint to avoid O(n) search complexity,
		 * but on second pass, start at 0 in pool 0.
		 */
		if ((start & mask) >= limit || pass > 0) {
			spin_unlock(&(pool->lock));
			pool = &(tbl->pools[0]);
			spin_lock(&(pool->lock));
			start = pool->start;
		} else {
			start &= mask;
		}
	}

	if (dev)
		boundary_size = ALIGN(dma_get_seg_boundary(dev) + 1,
				      1 << tbl->it_page_shift);
	else
		boundary_size = ALIGN(1UL << 32, 1 << tbl->it_page_shift);
	/* 4GB boundary for iseries_hv_alloc and iseries_hv_map */

	n = iommu_area_alloc(tbl->it_map, limit, start, npages, tbl->it_offset,
			     boundary_size >> tbl->it_page_shift, align_mask);
	if (n == -1) {
		if (likely(pass == 0)) {
			/* First try the pool from the start */
			pool->hint = pool->start;
			pass++;
			goto again;

		} else if (pass <= tbl->nr_pools) {
			/* Now try scanning all the other pools */
			spin_unlock(&(pool->lock));
			pool_nr = (pool_nr + 1) & (tbl->nr_pools - 1);
			pool = &tbl->pools[pool_nr];
			spin_lock(&(pool->lock));
			pool->hint = pool->start;
			pass++;
			goto again;

		} else {
			/* Give up */
			spin_unlock_irqrestore(&(pool->lock), flags);
			return DMA_MAPPING_ERROR;
		}
	}

	end = n + npages;

	/* Bump the hint to a new block for small allocs. */
	if (largealloc) {
		/* Don't bump to new block to avoid fragmentation */
		pool->hint = end;
	} else {
		/* Overflow will be taken care of at the next allocation */
		pool->hint = (end + tbl->it_blocksize - 1) &
		                ~(tbl->it_blocksize - 1);
	}

	/* Update handle for SG allocations */
	if (handle)
		*handle = end;

	spin_unlock_irqrestore(&(pool->lock), flags);

	return n;
}
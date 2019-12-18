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
typedef  scalar_t__ u32 ;
struct iommu_pool {unsigned int start; unsigned int hint; unsigned long end; int /*<<< orphan*/  lock; } ;
struct iommu_map_table {unsigned long nr_pools; void (* lazy_flush ) (struct iommu_map_table*) ;unsigned long poolsize; TYPE_1__* pools; int /*<<< orphan*/  flags; scalar_t__ table_shift; struct iommu_pool large_pool; } ;
struct TYPE_2__ {unsigned int start; unsigned int hint; unsigned int end; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IOMMU_HAS_LARGE_POOL ; 
 int /*<<< orphan*/  IOMMU_NO_SPAN_BOUND ; 
 scalar_t__ IOMMU_NR_POOLS ; 
 int /*<<< orphan*/  setup_iommu_pool_hash () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void iommu_tbl_pool_init(struct iommu_map_table *iommu,
			 unsigned long num_entries,
			 u32 table_shift,
			 void (*lazy_flush)(struct iommu_map_table *),
			 bool large_pool, u32 npools,
			 bool skip_span_boundary_check)
{
	unsigned int start, i;
	struct iommu_pool *p = &(iommu->large_pool);

	setup_iommu_pool_hash();
	if (npools == 0)
		iommu->nr_pools = IOMMU_NR_POOLS;
	else
		iommu->nr_pools = npools;
	BUG_ON(npools > IOMMU_NR_POOLS);

	iommu->table_shift = table_shift;
	iommu->lazy_flush = lazy_flush;
	start = 0;
	if (skip_span_boundary_check)
		iommu->flags |= IOMMU_NO_SPAN_BOUND;
	if (large_pool)
		iommu->flags |= IOMMU_HAS_LARGE_POOL;

	if (!large_pool)
		iommu->poolsize = num_entries/iommu->nr_pools;
	else
		iommu->poolsize = (num_entries * 3 / 4)/iommu->nr_pools;
	for (i = 0; i < iommu->nr_pools; i++) {
		spin_lock_init(&(iommu->pools[i].lock));
		iommu->pools[i].start = start;
		iommu->pools[i].hint = start;
		start += iommu->poolsize; /* start for next pool */
		iommu->pools[i].end = start - 1;
	}
	if (!large_pool)
		return;
	/* initialize large_pool */
	spin_lock_init(&(p->lock));
	p->start = start;
	p->hint = p->start;
	p->end = num_entries;
}
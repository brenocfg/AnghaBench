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
struct ldc_mtable_entry {int dummy; } ;
struct iommu_map_table {unsigned long poolsize; unsigned long nr_pools; int /*<<< orphan*/ * map; } ;
struct ldc_iommu {int /*<<< orphan*/ * page_table; struct iommu_map_table iommu_map_table; } ;
struct ldc_channel {int /*<<< orphan*/  id; struct ldc_iommu iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4v_ldc_set_map_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ldc_iommu_release(struct ldc_channel *lp)
{
	struct ldc_iommu *ldc_iommu = &lp->iommu;
	struct iommu_map_table *iommu = &ldc_iommu->iommu_map_table;
	unsigned long num_tsb_entries, tsbsize, order;

	(void) sun4v_ldc_set_map_table(lp->id, 0, 0);

	num_tsb_entries = iommu->poolsize * iommu->nr_pools;
	tsbsize = num_tsb_entries * sizeof(struct ldc_mtable_entry);
	order = get_order(tsbsize);

	free_pages((unsigned long) ldc_iommu->page_table, order);
	ldc_iommu->page_table = NULL;

	kfree(iommu->map);
	iommu->map = NULL;
}
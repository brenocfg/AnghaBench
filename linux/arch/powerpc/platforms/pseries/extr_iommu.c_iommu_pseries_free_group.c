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
struct iommu_table_group {scalar_t__ group; struct iommu_table** tables; } ;
struct iommu_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int /*<<< orphan*/  iommu_group_put (scalar_t__) ; 
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 
 int /*<<< orphan*/  kfree (struct iommu_table_group*) ; 

__attribute__((used)) static void iommu_pseries_free_group(struct iommu_table_group *table_group,
		const char *node_name)
{
	struct iommu_table *tbl;

	if (!table_group)
		return;

	tbl = table_group->tables[0];
#ifdef CONFIG_IOMMU_API
	if (table_group->group) {
		iommu_group_put(table_group->group);
		BUG_ON(table_group->group);
	}
#endif
	iommu_tce_table_put(tbl);

	kfree(table_group);
}
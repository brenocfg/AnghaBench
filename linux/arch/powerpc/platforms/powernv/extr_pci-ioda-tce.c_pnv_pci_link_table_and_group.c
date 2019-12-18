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
struct iommu_table_group_link {int /*<<< orphan*/  next; struct iommu_table_group* table_group; } ;
struct iommu_table_group {int /*<<< orphan*/ * tables; } ;
struct iommu_table {int /*<<< orphan*/  it_group_list; } ;

/* Variables and functions */
 long EINVAL ; 
 long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iommu_tce_table_get (struct iommu_table*) ; 
 struct iommu_table_group_link* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

long pnv_pci_link_table_and_group(int node, int num,
		struct iommu_table *tbl,
		struct iommu_table_group *table_group)
{
	struct iommu_table_group_link *tgl = NULL;

	if (WARN_ON(!tbl || !table_group))
		return -EINVAL;

	tgl = kzalloc_node(sizeof(struct iommu_table_group_link), GFP_KERNEL,
			node);
	if (!tgl)
		return -ENOMEM;

	tgl->table_group = table_group;
	list_add_rcu(&tgl->next, &tbl->it_group_list);

	table_group->tables[num] = iommu_tce_table_get(tbl);

	return 0;
}
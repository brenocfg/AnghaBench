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
struct iommu_table_group {struct iommu_table** tables; } ;
struct iommu_table {int /*<<< orphan*/  it_kref; int /*<<< orphan*/  it_group_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iommu_table_group*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 void* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct iommu_table_group *iommu_pseries_alloc_group(int node)
{
	struct iommu_table_group *table_group;
	struct iommu_table *tbl;

	table_group = kzalloc_node(sizeof(struct iommu_table_group), GFP_KERNEL,
			   node);
	if (!table_group)
		return NULL;

	tbl = kzalloc_node(sizeof(struct iommu_table), GFP_KERNEL, node);
	if (!tbl)
		goto free_group;

	INIT_LIST_HEAD_RCU(&tbl->it_group_list);
	kref_init(&tbl->it_kref);

	table_group->tables[0] = tbl;

	return table_group;

free_group:
	kfree(table_group);
	return NULL;
}
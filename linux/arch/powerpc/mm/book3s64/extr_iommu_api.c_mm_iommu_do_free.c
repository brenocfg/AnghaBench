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
struct mm_iommu_table_group_mem_t {int /*<<< orphan*/  hpas; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mm_iommu_table_group_mem_t*) ; 
 int /*<<< orphan*/  mm_iommu_unpin (struct mm_iommu_table_group_mem_t*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mm_iommu_do_free(struct mm_iommu_table_group_mem_t *mem)
{

	mm_iommu_unpin(mem);
	vfree(mem->hpas);
	kfree(mem);
}
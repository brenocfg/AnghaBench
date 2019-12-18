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
struct mm_struct {int dummy; } ;
struct mm_iommu_table_group_mem_t {scalar_t__ dev_hpa; unsigned long ua; int /*<<< orphan*/ * hpas; } ;

/* Variables and functions */
 unsigned long MM_IOMMU_TABLE_GROUP_PAGE_DIRTY ; 
 scalar_t__ MM_IOMMU_TABLE_INVALID_HPA ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct mm_iommu_table_group_mem_t* mm_iommu_lookup_rm (struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ vmalloc_to_phys (void*) ; 

extern void mm_iommu_ua_mark_dirty_rm(struct mm_struct *mm, unsigned long ua)
{
	struct mm_iommu_table_group_mem_t *mem;
	long entry;
	void *va;
	unsigned long *pa;

	mem = mm_iommu_lookup_rm(mm, ua, PAGE_SIZE);
	if (!mem)
		return;

	if (mem->dev_hpa != MM_IOMMU_TABLE_INVALID_HPA)
		return;

	entry = (ua - mem->ua) >> PAGE_SHIFT;
	va = &mem->hpas[entry];

	pa = (void *) vmalloc_to_phys(va);
	if (!pa)
		return;

	*pa |= MM_IOMMU_TABLE_GROUP_PAGE_DIRTY;
}
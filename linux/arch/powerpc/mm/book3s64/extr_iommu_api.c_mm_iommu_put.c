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
struct mm_iommu_table_group_mem_t {scalar_t__ used; scalar_t__ dev_hpa; unsigned long entries; int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 long EBUSY ; 
 long ENOENT ; 
 scalar_t__ MM_IOMMU_TABLE_INVALID_HPA ; 
 int /*<<< orphan*/  account_locked_vm (struct mm_struct*,unsigned long,int) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_list_mutex ; 
 int /*<<< orphan*/  mm_iommu_release (struct mm_iommu_table_group_mem_t*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

long mm_iommu_put(struct mm_struct *mm, struct mm_iommu_table_group_mem_t *mem)
{
	long ret = 0;
	unsigned long unlock_entries = 0;

	mutex_lock(&mem_list_mutex);

	if (mem->used == 0) {
		ret = -ENOENT;
		goto unlock_exit;
	}

	--mem->used;
	/* There are still users, exit */
	if (mem->used)
		goto unlock_exit;

	/* Are there still mappings? */
	if (atomic_cmpxchg(&mem->mapped, 1, 0) != 1) {
		++mem->used;
		ret = -EBUSY;
		goto unlock_exit;
	}

	if (mem->dev_hpa == MM_IOMMU_TABLE_INVALID_HPA)
		unlock_entries = mem->entries;

	/* @mapped became 0 so now mappings are disabled, release the region */
	mm_iommu_release(mem);

unlock_exit:
	mutex_unlock(&mem_list_mutex);

	account_locked_vm(mm, unlock_entries, false);

	return ret;
}
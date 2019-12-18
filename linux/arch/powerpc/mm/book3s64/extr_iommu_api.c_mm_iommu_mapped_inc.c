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
struct mm_iommu_table_group_mem_t {int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 long ENXIO ; 
 scalar_t__ atomic64_inc_not_zero (int /*<<< orphan*/ *) ; 

long mm_iommu_mapped_inc(struct mm_iommu_table_group_mem_t *mem)
{
	if (atomic64_inc_not_zero(&mem->mapped))
		return 0;

	/* Last mm_iommu_put() has been called, no more mappings allowed() */
	return -ENXIO;
}
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
typedef  scalar_t__ u64 ;
struct fadump_mrange_info {int mem_range_cnt; int max_mem_ranges; int /*<<< orphan*/  name; struct fadump_memory_range* mem_ranges; } ;
struct fadump_memory_range {scalar_t__ base; scalar_t__ size; } ;

/* Variables and functions */
 int fadump_alloc_mem_ranges (struct fadump_mrange_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int fadump_add_mem_range(struct fadump_mrange_info *mrange_info,
				       u64 base, u64 end)
{
	struct fadump_memory_range *mem_ranges = mrange_info->mem_ranges;
	bool is_adjacent = false;
	u64 start, size;

	if (base == end)
		return 0;

	/*
	 * Fold adjacent memory ranges to bring down the memory ranges/
	 * PT_LOAD segments count.
	 */
	if (mrange_info->mem_range_cnt) {
		start = mem_ranges[mrange_info->mem_range_cnt - 1].base;
		size  = mem_ranges[mrange_info->mem_range_cnt - 1].size;

		if ((start + size) == base)
			is_adjacent = true;
	}
	if (!is_adjacent) {
		/* resize the array on reaching the limit */
		if (mrange_info->mem_range_cnt == mrange_info->max_mem_ranges) {
			int ret;

			ret = fadump_alloc_mem_ranges(mrange_info);
			if (ret)
				return ret;

			/* Update to the new resized array */
			mem_ranges = mrange_info->mem_ranges;
		}

		start = base;
		mem_ranges[mrange_info->mem_range_cnt].base = start;
		mrange_info->mem_range_cnt++;
	}

	mem_ranges[mrange_info->mem_range_cnt - 1].size = (end - start);
	pr_debug("%s_memory_range[%d] [%#016llx-%#016llx], %#llx bytes\n",
		 mrange_info->name, (mrange_info->mem_range_cnt - 1),
		 start, end - 1, (end - start));
	return 0;
}
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
typedef  int u64 ;
struct fadump_mrange_info {int mem_ranges_sz; int max_mem_ranges; struct fadump_memory_range* mem_ranges; int /*<<< orphan*/  name; } ;
struct fadump_memory_range {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  fadump_free_mem_ranges (struct fadump_mrange_info*) ; 
 struct fadump_memory_range* krealloc (struct fadump_memory_range*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fadump_alloc_mem_ranges(struct fadump_mrange_info *mrange_info)
{
	struct fadump_memory_range *new_array;
	u64 new_size;

	new_size = mrange_info->mem_ranges_sz + PAGE_SIZE;
	pr_debug("Allocating %llu bytes of memory for %s memory ranges\n",
		 new_size, mrange_info->name);

	new_array = krealloc(mrange_info->mem_ranges, new_size, GFP_KERNEL);
	if (new_array == NULL) {
		pr_err("Insufficient memory for setting up %s memory ranges\n",
		       mrange_info->name);
		fadump_free_mem_ranges(mrange_info);
		return -ENOMEM;
	}

	mrange_info->mem_ranges = new_array;
	mrange_info->mem_ranges_sz = new_size;
	mrange_info->max_mem_ranges = (new_size /
				       sizeof(struct fadump_memory_range));
	return 0;
}
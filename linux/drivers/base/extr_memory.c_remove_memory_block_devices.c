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
struct memory_block {scalar_t__ section_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFN_DOWN (unsigned long) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct memory_block* find_memory_block_by_id (unsigned long) ; 
 int /*<<< orphan*/  mem_sysfs_mutex ; 
 int /*<<< orphan*/  memory_block_size_bytes () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long pfn_to_block_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_memory (struct memory_block*) ; 
 int /*<<< orphan*/  unregister_memory_block_under_nodes (struct memory_block*) ; 

void remove_memory_block_devices(unsigned long start, unsigned long size)
{
	const unsigned long start_block_id = pfn_to_block_id(PFN_DOWN(start));
	const unsigned long end_block_id = pfn_to_block_id(PFN_DOWN(start + size));
	struct memory_block *mem;
	unsigned long block_id;

	if (WARN_ON_ONCE(!IS_ALIGNED(start, memory_block_size_bytes()) ||
			 !IS_ALIGNED(size, memory_block_size_bytes())))
		return;

	mutex_lock(&mem_sysfs_mutex);
	for (block_id = start_block_id; block_id != end_block_id; block_id++) {
		mem = find_memory_block_by_id(block_id);
		if (WARN_ON_ONCE(!mem))
			continue;
		mem->section_count = 0;
		unregister_memory_block_under_nodes(mem);
		unregister_memory(mem);
	}
	mutex_unlock(&mem_sysfs_mutex);
}
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
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_OFFLINE ; 
 int /*<<< orphan*/  PFN_DOWN (unsigned long) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct memory_block* find_memory_block_by_id (unsigned long) ; 
 int init_memory_block (struct memory_block**,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_sysfs_mutex ; 
 int /*<<< orphan*/  memory_block_size_bytes () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* pfn_to_block_id (int /*<<< orphan*/ ) ; 
 scalar_t__ sections_per_block ; 
 int /*<<< orphan*/  unregister_memory (struct memory_block*) ; 

int create_memory_block_devices(unsigned long start, unsigned long size)
{
	const unsigned long start_block_id = pfn_to_block_id(PFN_DOWN(start));
	unsigned long end_block_id = pfn_to_block_id(PFN_DOWN(start + size));
	struct memory_block *mem;
	unsigned long block_id;
	int ret = 0;

	if (WARN_ON_ONCE(!IS_ALIGNED(start, memory_block_size_bytes()) ||
			 !IS_ALIGNED(size, memory_block_size_bytes())))
		return -EINVAL;

	mutex_lock(&mem_sysfs_mutex);
	for (block_id = start_block_id; block_id != end_block_id; block_id++) {
		ret = init_memory_block(&mem, block_id, MEM_OFFLINE);
		if (ret)
			break;
		mem->section_count = sections_per_block;
	}
	if (ret) {
		end_block_id = block_id;
		for (block_id = start_block_id; block_id != end_block_id;
		     block_id++) {
			mem = find_memory_block_by_id(block_id);
			mem->section_count = 0;
			unregister_memory(mem);
		}
	}
	mutex_unlock(&mem_sysfs_mutex);
	return ret;
}
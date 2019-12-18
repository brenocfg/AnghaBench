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
struct memory_block {unsigned long start_section_nr; unsigned long state; int /*<<< orphan*/  nid; int /*<<< orphan*/  phys_device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  arch_get_memory_phys_device (unsigned long) ; 
 struct memory_block* find_memory_block_by_id (unsigned long) ; 
 struct memory_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int register_memory (struct memory_block*) ; 
 unsigned long section_nr_to_pfn (unsigned long) ; 
 unsigned long sections_per_block ; 

__attribute__((used)) static int init_memory_block(struct memory_block **memory,
			     unsigned long block_id, unsigned long state)
{
	struct memory_block *mem;
	unsigned long start_pfn;
	int ret = 0;

	mem = find_memory_block_by_id(block_id);
	if (mem) {
		put_device(&mem->dev);
		return -EEXIST;
	}
	mem = kzalloc(sizeof(*mem), GFP_KERNEL);
	if (!mem)
		return -ENOMEM;

	mem->start_section_nr = block_id * sections_per_block;
	mem->state = state;
	start_pfn = section_nr_to_pfn(mem->start_section_nr);
	mem->phys_device = arch_get_memory_phys_device(start_pfn);
	mem->nid = NUMA_NO_NODE;

	ret = register_memory(mem);

	*memory = mem;
	return ret;
}
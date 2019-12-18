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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ MEM_GOING_OFFLINE ; 
 scalar_t__ MEM_OFFLINE ; 
 scalar_t__ MEM_ONLINE ; 
 unsigned long PFN_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_memblock_state ; 
 int /*<<< orphan*/  check_memblock_online ; 
 scalar_t__ offline_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ walk_memory_blocks (unsigned long const,unsigned long const,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool memtrace_offline_pages(u32 nid, u64 start_pfn, u64 nr_pages)
{
	const unsigned long start = PFN_PHYS(start_pfn);
	const unsigned long size = PFN_PHYS(nr_pages);

	if (walk_memory_blocks(start, size, NULL, check_memblock_online))
		return false;

	walk_memory_blocks(start, size, (void *)MEM_GOING_OFFLINE,
			   change_memblock_state);

	if (offline_pages(start_pfn, nr_pages)) {
		walk_memory_blocks(start, size, (void *)MEM_ONLINE,
				   change_memblock_state);
		return false;
	}

	walk_memory_blocks(start, size, (void *)MEM_OFFLINE,
			   change_memblock_state);


	return true;
}
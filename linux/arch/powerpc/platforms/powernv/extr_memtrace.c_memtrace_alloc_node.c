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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __remove_memory (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lock_device_hotplug () ; 
 int memory_block_size_bytes () ; 
 int memtrace_offline_pages (int /*<<< orphan*/ ,int,int) ; 
 int node_end_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_spanned_pages (int /*<<< orphan*/ ) ; 
 int node_start_pfn (int /*<<< orphan*/ ) ; 
 int round_down (int,int) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 

__attribute__((used)) static u64 memtrace_alloc_node(u32 nid, u64 size)
{
	u64 start_pfn, end_pfn, nr_pages, pfn;
	u64 base_pfn;
	u64 bytes = memory_block_size_bytes();

	if (!node_spanned_pages(nid))
		return 0;

	start_pfn = node_start_pfn(nid);
	end_pfn = node_end_pfn(nid);
	nr_pages = size >> PAGE_SHIFT;

	/* Trace memory needs to be aligned to the size */
	end_pfn = round_down(end_pfn - nr_pages, nr_pages);

	lock_device_hotplug();
	for (base_pfn = end_pfn; base_pfn > start_pfn; base_pfn -= nr_pages) {
		if (memtrace_offline_pages(nid, base_pfn, nr_pages) == true) {
			/*
			 * Remove memory in memory block size chunks so that
			 * iomem resources are always split to the same size and
			 * we never try to remove memory that spans two iomem
			 * resources.
			 */
			end_pfn = base_pfn + nr_pages;
			for (pfn = base_pfn; pfn < end_pfn; pfn += bytes>> PAGE_SHIFT) {
				__remove_memory(nid, pfn << PAGE_SHIFT, bytes);
			}
			unlock_device_hotplug();
			return base_pfn << PAGE_SHIFT;
		}
	}
	unlock_device_hotplug();

	return 0;
}
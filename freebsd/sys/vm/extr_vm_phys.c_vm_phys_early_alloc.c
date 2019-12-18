#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; int domain; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 TYPE_1__* mem_affinity ; 
 int /*<<< orphan*/  panic (char*) ; 
 size_t* phys_avail ; 
 size_t round_page (size_t) ; 
 int /*<<< orphan*/  vm_phys_avail_check (int) ; 
 scalar_t__ vm_phys_avail_size (int) ; 
 scalar_t__ vm_phys_avail_split (size_t,int) ; 

vm_paddr_t
vm_phys_early_alloc(int domain, size_t alloc_size)
{
	int i, mem_index, biggestone;
	vm_paddr_t pa, mem_start, mem_end, size, biggestsize, align;


	/*
	 * Search the mem_affinity array for the biggest address
	 * range in the desired domain.  This is used to constrain
	 * the phys_avail selection below.
	 */
	biggestsize = 0;
	mem_index = 0;
	mem_start = 0;
	mem_end = -1;
#ifdef NUMA
	if (mem_affinity != NULL) {
		for (i = 0; ; i++) {
			size = mem_affinity[i].end - mem_affinity[i].start;
			if (size == 0)
				break;
			if (mem_affinity[i].domain != domain)
				continue;
			if (size > biggestsize) {
				mem_index = i;
				biggestsize = size;
			}
		}
		mem_start = mem_affinity[mem_index].start;
		mem_end = mem_affinity[mem_index].end;
	}
#endif

	/*
	 * Now find biggest physical segment in within the desired
	 * numa domain.
	 */
	biggestsize = 0;
	biggestone = 0;
	for (i = 0; phys_avail[i + 1] != 0; i += 2) {
		/* skip regions that are out of range */
		if (phys_avail[i+1] - alloc_size < mem_start ||
		    phys_avail[i+1] > mem_end)
			continue;
		size = vm_phys_avail_size(i);
		if (size > biggestsize) {
			biggestone = i;
			biggestsize = size;
		}
	}
	alloc_size = round_page(alloc_size);

	/*
	 * Grab single pages from the front to reduce fragmentation.
	 */
	if (alloc_size == PAGE_SIZE) {
		pa = phys_avail[biggestone];
		phys_avail[biggestone] += PAGE_SIZE;
		vm_phys_avail_check(biggestone);
		return (pa);
	}

	/*
	 * Naturally align large allocations.
	 */
	align = phys_avail[biggestone + 1] & (alloc_size - 1);
	if (alloc_size + align > biggestsize)
		panic("cannot find a large enough size\n");
	if (align != 0 &&
	    vm_phys_avail_split(phys_avail[biggestone + 1] - align,
	    biggestone) != 0)
		/* Wasting memory. */
		phys_avail[biggestone + 1] -= align;

	phys_avail[biggestone + 1] -= alloc_size;
	vm_phys_avail_check(biggestone);
	pa = phys_avail[biggestone + 1];
	return (pa);
}
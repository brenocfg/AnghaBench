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
typedef  int u_long ;
struct vm_map {int dummy; } ;
struct TYPE_2__ {int v_page_count; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int memguard_mapsize ; 
 int memguard_physlimit ; 
 int round_page (int) ; 
 TYPE_1__ vm_cnt ; 
 int vm_map_max (struct vm_map const*) ; 
 int vm_map_min (struct vm_map const*) ; 
 int vm_memguard_divisor ; 

unsigned long
memguard_fudge(unsigned long km_size, const struct vm_map *parent_map)
{
	u_long mem_pgs, parent_size;

	vm_memguard_divisor = 10;
	/* CTFLAG_RDTUN doesn't work during the early boot process. */
	TUNABLE_INT_FETCH("vm.memguard.divisor", &vm_memguard_divisor);

	parent_size = vm_map_max(parent_map) - vm_map_min(parent_map) +
	    PAGE_SIZE;
	/* Pick a conservative value if provided value sucks. */
	if ((vm_memguard_divisor <= 0) ||
	    ((parent_size / vm_memguard_divisor) == 0))
		vm_memguard_divisor = 10;
	/*
	 * Limit consumption of physical pages to
	 * 1/vm_memguard_divisor of system memory.  If the KVA is
	 * smaller than this then the KVA limit comes into play first.
	 * This prevents memguard's page promotions from completely
	 * using up memory, since most malloc(9) calls are sub-page.
	 */
	mem_pgs = vm_cnt.v_page_count;
	memguard_physlimit = (mem_pgs / vm_memguard_divisor) * PAGE_SIZE;
	/*
	 * We want as much KVA as we can take safely.  Use at most our
	 * allotted fraction of the parent map's size.  Limit this to
	 * twice the physical memory to avoid using too much memory as
	 * pagetable pages (size must be multiple of PAGE_SIZE).
	 */
	memguard_mapsize = round_page(parent_size / vm_memguard_divisor);
	if (memguard_mapsize / (2 * PAGE_SIZE) > mem_pgs)
		memguard_mapsize = mem_pgs * 2 * PAGE_SIZE;
	if (km_size + memguard_mapsize > parent_size)
		memguard_mapsize = 0;
	return (km_size + memguard_mapsize);
}
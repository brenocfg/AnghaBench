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
typedef  int vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int PHYS_TO_DMAP (scalar_t__) ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  cpu_icache_sync_range (int,int) ; 
 int imin (scalar_t__,int) ; 
 scalar_t__ pmap_extract (int /*<<< orphan*/ ,int) ; 

void
pmap_sync_icache(pmap_t pmap, vm_offset_t va, vm_size_t sz)
{

	if (va >= VM_MIN_KERNEL_ADDRESS) {
		cpu_icache_sync_range(va, sz);
	} else {
		u_int len, offset;
		vm_paddr_t pa;

		/* Find the length of data in this page to flush */
		offset = va & PAGE_MASK;
		len = imin(PAGE_SIZE - offset, sz);

		while (sz != 0) {
			/* Extract the physical address & find it in the DMAP */
			pa = pmap_extract(pmap, va);
			if (pa != 0)
				cpu_icache_sync_range(PHYS_TO_DMAP(pa), len);

			/* Move to the next page */
			sz -= len;
			va += len;
			/* Set the length for the next iteration */
			len = imin(PAGE_SIZE, sz);
		}
	}
}
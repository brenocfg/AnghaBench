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
typedef  int vm_offset_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int MAX_PHYS_ADDR ; 
 int PAGE_SIZE ; 
 scalar_t__ hwcnt ; 
 int /*<<< orphan*/  hwregions ; 
 scalar_t__ insert_region (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nitems (int /*<<< orphan*/ ) ; 
 int round_page (int) ; 
 int trunc_page (int) ; 

void
arm_physmem_hardware_region(uint64_t pa, uint64_t sz)
{
	vm_offset_t adj;

	/*
	 * Filter out the page at PA 0x00000000.  The VM can't handle it, as
	 * pmap_extract() == 0 means failure.
	 */
	if (pa == 0) {
		if (sz <= PAGE_SIZE)
			return;
		pa  = PAGE_SIZE;
		sz -= PAGE_SIZE;
	} else if (pa > MAX_PHYS_ADDR) {
		/* This range is past usable memory, ignore it */
		return;
	}

	/*
	 * Also filter out the page at the end of the physical address space --
	 * if addr is non-zero and addr+size is zero we wrapped to the next byte
	 * beyond what vm_paddr_t can express.  That leads to a NULL pointer
	 * deref early in startup; work around it by leaving the last page out.
	 *
	 * XXX This just in:  subtract out a whole megabyte, not just 1 page.
	 * Reducing the size by anything less than 1MB results in the NULL
	 * pointer deref in _vm_map_lock_read().  Better to give up a megabyte
	 * than leave some folks with an unusable system while we investigate.
	 */
	if ((pa + sz) > (MAX_PHYS_ADDR - 1024 * 1024)) {
		sz = MAX_PHYS_ADDR - pa + 1;
		if (sz <= 1024 * 1024)
			return;
		sz -= 1024 * 1024;
	}

	/*
	 * Round the starting address up to a page boundary, and truncate the
	 * ending page down to a page boundary.
	 */
	adj = round_page(pa) - pa;
	pa  = round_page(pa);
	sz  = trunc_page(sz - adj);

	if (sz > 0 && hwcnt < nitems(hwregions))
		hwcnt = insert_region(hwregions, hwcnt, pa, sz, 0);
}
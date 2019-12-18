#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_page_bits_t ;
struct TYPE_10__ {int valid; int dirty; } ;

/* Variables and functions */
 int DEV_BSHIFT ; 
 int DEV_BSIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PGA_NOSYNC ; 
 int VM_PAGE_BITS_ALL ; 
 int /*<<< orphan*/  pmap_clear_modify (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_zero_page_area (TYPE_1__*,int,int) ; 
 int rounddown2 (int,int) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 
 int vm_page_bits (int,int) ; 
 int /*<<< orphan*/  vm_page_bits_set (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  vm_page_clear_dirty_mask (TYPE_1__*,int) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 

void
vm_page_set_validclean(vm_page_t m, int base, int size)
{
	vm_page_bits_t oldvalid, pagebits;
	int endoff, frag;

	vm_page_assert_busied(m);
	if (size == 0)	/* handle degenerate case */
		return;

	/*
	 * If the base is not DEV_BSIZE aligned and the valid
	 * bit is clear, we have to zero out a portion of the
	 * first block.
	 */
	if ((frag = rounddown2(base, DEV_BSIZE)) != base &&
	    (m->valid & ((vm_page_bits_t)1 << (base >> DEV_BSHIFT))) == 0)
		pmap_zero_page_area(m, frag, base - frag);

	/*
	 * If the ending offset is not DEV_BSIZE aligned and the
	 * valid bit is clear, we have to zero out a portion of
	 * the last block.
	 */
	endoff = base + size;
	if ((frag = rounddown2(endoff, DEV_BSIZE)) != endoff &&
	    (m->valid & ((vm_page_bits_t)1 << (endoff >> DEV_BSHIFT))) == 0)
		pmap_zero_page_area(m, endoff,
		    DEV_BSIZE - (endoff & (DEV_BSIZE - 1)));

	/*
	 * Set valid, clear dirty bits.  If validating the entire
	 * page we can safely clear the pmap modify bit.  We also
	 * use this opportunity to clear the PGA_NOSYNC flag.  If a process
	 * takes a write fault on a MAP_NOSYNC memory area the flag will
	 * be set again.
	 *
	 * We set valid bits inclusive of any overlap, but we can only
	 * clear dirty bits for DEV_BSIZE chunks that are fully within
	 * the range.
	 */
	oldvalid = m->valid;
	pagebits = vm_page_bits(base, size);
	if (vm_page_xbusied(m))
		m->valid |= pagebits;
	else
		vm_page_bits_set(m, &m->valid, pagebits);
#if 0	/* NOT YET */
	if ((frag = base & (DEV_BSIZE - 1)) != 0) {
		frag = DEV_BSIZE - frag;
		base += frag;
		size -= frag;
		if (size < 0)
			size = 0;
	}
	pagebits = vm_page_bits(base, size & (DEV_BSIZE - 1));
#endif
	if (base == 0 && size == PAGE_SIZE) {
		/*
		 * The page can only be modified within the pmap if it is
		 * mapped, and it can only be mapped if it was previously
		 * fully valid.
		 */
		if (oldvalid == VM_PAGE_BITS_ALL)
			/*
			 * Perform the pmap_clear_modify() first.  Otherwise,
			 * a concurrent pmap operation, such as
			 * pmap_protect(), could clear a modification in the
			 * pmap and set the dirty field on the page before
			 * pmap_clear_modify() had begun and after the dirty
			 * field was cleared here.
			 */
			pmap_clear_modify(m);
		m->dirty = 0;
		vm_page_aflag_clear(m, PGA_NOSYNC);
	} else if (oldvalid != VM_PAGE_BITS_ALL && vm_page_xbusied(m))
		m->dirty &= ~pagebits;
	else
		vm_page_clear_dirty_mask(m, pagebits);
}
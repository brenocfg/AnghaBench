#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_page_bits_t ;
struct TYPE_7__ {int valid; int dirty; } ;

/* Variables and functions */
 int DEV_BSHIFT ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  pmap_zero_page_area (TYPE_1__*,int,int) ; 
 int rounddown2 (int,int) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 
 int vm_page_bits (int,int) ; 
 int /*<<< orphan*/  vm_page_bits_set (TYPE_1__*,int*,int) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 

void
vm_page_set_valid_range(vm_page_t m, int base, int size)
{
	int endoff, frag;
	vm_page_bits_t pagebits;

	vm_page_assert_busied(m);
	if (size == 0)	/* handle degenerate case */
		return;

	/*
	 * If the base is not DEV_BSIZE aligned and the valid
	 * bit is clear, we have to zero out a portion of the
	 * first block.
	 */
	if ((frag = rounddown2(base, DEV_BSIZE)) != base &&
	    (m->valid & (1 << (base >> DEV_BSHIFT))) == 0)
		pmap_zero_page_area(m, frag, base - frag);

	/*
	 * If the ending offset is not DEV_BSIZE aligned and the
	 * valid bit is clear, we have to zero out a portion of
	 * the last block.
	 */
	endoff = base + size;
	if ((frag = rounddown2(endoff, DEV_BSIZE)) != endoff &&
	    (m->valid & (1 << (endoff >> DEV_BSHIFT))) == 0)
		pmap_zero_page_area(m, endoff,
		    DEV_BSIZE - (endoff & (DEV_BSIZE - 1)));

	/*
	 * Assert that no previously invalid block that is now being validated
	 * is already dirty.
	 */
	KASSERT((~m->valid & vm_page_bits(base, size) & m->dirty) == 0,
	    ("vm_page_set_valid_range: page %p is dirty", m));

	/*
	 * Set valid bits inclusive of any overlap.
	 */
	pagebits = vm_page_bits(base, size);
	if (vm_page_xbusied(m))
		m->valid |= pagebits;
	else
		vm_page_bits_set(m, &m->valid, pagebits);
}
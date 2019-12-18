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
struct drbd_bitmap {int bm_bits; scalar_t__ bm_number_of_pages; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int BITS_PER_LONG_MASK ; 
 int BITS_PER_PAGE_MASK ; 
 unsigned long* bm_map_pidx (struct drbd_bitmap*,scalar_t__) ; 
 int /*<<< orphan*/  bm_unmap (unsigned long*) ; 
 unsigned long cpu_to_lel (unsigned long) ; 
 int hweight_long (unsigned long) ; 

__attribute__((used)) static int bm_clear_surplus(struct drbd_bitmap *b)
{
	unsigned long mask;
	unsigned long *p_addr, *bm;
	int tmp;
	int cleared = 0;

	/* number of bits modulo bits per page */
	tmp = (b->bm_bits & BITS_PER_PAGE_MASK);
	/* mask the used bits of the word containing the last bit */
	mask = (1UL << (tmp & BITS_PER_LONG_MASK)) -1;
	/* bitmap is always stored little endian,
	 * on disk and in core memory alike */
	mask = cpu_to_lel(mask);

	p_addr = bm_map_pidx(b, b->bm_number_of_pages - 1);
	bm = p_addr + (tmp/BITS_PER_LONG);
	if (mask) {
		/* If mask != 0, we are not exactly aligned, so bm now points
		 * to the long containing the last bit.
		 * If mask == 0, bm already points to the word immediately
		 * after the last (long word aligned) bit. */
		cleared = hweight_long(*bm & ~mask);
		*bm &= mask;
		bm++;
	}

	if (BITS_PER_LONG == 32 && ((bm - p_addr) & 1) == 1) {
		/* on a 32bit arch, we may need to zero out
		 * a padding long to align with a 64bit remote */
		cleared += hweight_long(*bm);
		*bm = 0;
	}
	bm_unmap(p_addr);
	return cleared;
}
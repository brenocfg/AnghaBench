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

/* Variables and functions */
 int ZU (int) ; 
 size_t reg_size_compute (int,int,int) ; 

__attribute__((used)) static int
slab_size(int lg_page, int lg_base, int lg_delta, int ndelta) {
	size_t page = (ZU(1) << lg_page);
	size_t reg_size = reg_size_compute(lg_base, lg_delta, ndelta);

	size_t try_slab_size = page;
	size_t try_nregs = try_slab_size / reg_size;
	size_t perfect_slab_size = 0;
	bool perfect = false;
	/*
	 * This loop continues until we find the least common multiple of the
	 * page size and size class size.  Size classes are all of the form
	 * base + ndelta * delta == (ndelta + base/ndelta) * delta, which is
	 * (ndelta + ngroup) * delta.  The way we choose slabbing strategies
	 * means that delta is at most the page size and ndelta < ngroup.  So
	 * the loop executes for at most 2 * ngroup - 1 iterations, which is
	 * also the bound on the number of pages in a slab chosen by default.
	 * With the current default settings, this is at most 7.
	 */
	while (!perfect) {
		perfect_slab_size = try_slab_size;
		size_t perfect_nregs = try_nregs;
		try_slab_size += page;
		try_nregs = try_slab_size / reg_size;
		if (perfect_slab_size == perfect_nregs * reg_size) {
			perfect = true;
		}
	}
	return (int)(perfect_slab_size / page);
}
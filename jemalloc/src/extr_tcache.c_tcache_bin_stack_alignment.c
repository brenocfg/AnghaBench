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
 int LG_SIZEOF_PTR ; 
 size_t PAGE ; 
 size_t pow2_ceil_zu (size_t) ; 

__attribute__((used)) static size_t
tcache_bin_stack_alignment (size_t size) {
	/*
	 * 1) Align to at least PAGE, to minimize the # of TLBs needed by the
	 * smaller sizes; also helps if the larger sizes don't get used at all.
	 * 2) On 32-bit the pointers won't be compressed; use minimal alignment.
	 */
	if (LG_SIZEOF_PTR < 3 || size < PAGE) {
		return PAGE;
	}
	/* Align pow2 to avoid overflow the cache bin compressed pointers. */
	return pow2_ceil_zu(size);
}
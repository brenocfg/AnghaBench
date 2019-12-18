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
 size_t PAGE_MASK ; 
 size_t SC_LARGE_MAXCLASS ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t sz_large_pad ; 
 size_t sz_pind2sz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sz_psz2ind (size_t) ; 
 size_t sz_psz_quantize_floor (size_t) ; 

size_t
sz_psz_quantize_ceil(size_t size) {
	size_t ret;

	assert(size > 0);
	assert(size - sz_large_pad <= SC_LARGE_MAXCLASS);
	assert((size & PAGE_MASK) == 0);

	ret = sz_psz_quantize_floor(size);
	if (ret < size) {
		/*
		 * Skip a quantization that may have an adequately large extent,
		 * because under-sized extents may be mixed in.  This only
		 * happens when an unusual size is requested, i.e. for aligned
		 * allocation, and is just one of several places where linear
		 * search would potentially find sufficiently aligned available
		 * memory somewhere lower.
		 */
		ret = sz_pind2sz(sz_psz2ind(ret - sz_large_pad + 1)) +
		    sz_large_pad;
	}
	return ret;
}
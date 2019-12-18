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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 int MALLOCX_ARENA (unsigned int) ; 
 int MALLOCX_TCACHE_NONE ; 
 unsigned int NLARGE ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*,...) ; 
 int /*<<< orphan*/  assert_zu_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t get_large_size (unsigned int) ; 
 unsigned int get_nlarge () ; 
 unsigned int get_nsmall () ; 
 size_t get_small_size (unsigned int) ; 
 int /*<<< orphan*/  ivsalloc (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ malloc (unsigned int) ; 
 void* mallocx (size_t,int) ; 
 int /*<<< orphan*/ * tsdn_fetch () ; 

__attribute__((used)) static void
do_arena_reset_pre(unsigned arena_ind, void ***ptrs, unsigned *nptrs) {
#define NLARGE	32
	unsigned nsmall, nlarge, i;
	size_t sz;
	int flags;
	tsdn_t *tsdn;

	flags = MALLOCX_ARENA(arena_ind) | MALLOCX_TCACHE_NONE;

	nsmall = get_nsmall();
	nlarge = get_nlarge() > NLARGE ? NLARGE : get_nlarge();
	*nptrs = nsmall + nlarge;
	*ptrs = (void **)malloc(*nptrs * sizeof(void *));
	assert_ptr_not_null(*ptrs, "Unexpected malloc() failure");

	/* Allocate objects with a wide range of sizes. */
	for (i = 0; i < nsmall; i++) {
		sz = get_small_size(i);
		(*ptrs)[i] = mallocx(sz, flags);
		assert_ptr_not_null((*ptrs)[i],
		    "Unexpected mallocx(%zu, %#x) failure", sz, flags);
	}
	for (i = 0; i < nlarge; i++) {
		sz = get_large_size(i);
		(*ptrs)[nsmall + i] = mallocx(sz, flags);
		assert_ptr_not_null((*ptrs)[i],
		    "Unexpected mallocx(%zu, %#x) failure", sz, flags);
	}

	tsdn = tsdn_fetch();

	/* Verify allocations. */
	for (i = 0; i < *nptrs; i++) {
		assert_zu_gt(ivsalloc(tsdn, (*ptrs)[i]), 0,
		    "Allocation should have queryable size");
	}
}
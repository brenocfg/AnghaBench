#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {void* (* alloc ) (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t,int*,int*,unsigned int) ;} ;
typedef  TYPE_1__ extent_hooks_t ;

/* Variables and functions */
 size_t HUGEPAGE ; 
 size_t HUGEPAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* extent_alloc_mmap (int /*<<< orphan*/ *,size_t,size_t,int*,int*) ; 
 TYPE_1__ extent_hooks_default ; 
 int /*<<< orphan*/  post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* stub1 (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t,int*,int*,unsigned int) ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 scalar_t__ tsdn_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsdn_tsd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
base_map(tsdn_t *tsdn, extent_hooks_t *extent_hooks, unsigned ind, size_t size) {
	void *addr;
	bool zero = true;
	bool commit = true;

	/* Use huge page sizes and alignment regardless of opt_metadata_thp. */
	assert(size == HUGEPAGE_CEILING(size));
	size_t alignment = HUGEPAGE;
	if (extent_hooks == &extent_hooks_default) {
		addr = extent_alloc_mmap(NULL, size, alignment, &zero, &commit);
	} else {
		/* No arena context as we are creating new arenas. */
		tsd_t *tsd = tsdn_null(tsdn) ? tsd_fetch() : tsdn_tsd(tsdn);
		pre_reentrancy(tsd, NULL);
		addr = extent_hooks->alloc(extent_hooks, NULL, size, alignment,
		    &zero, &commit, ind);
		post_reentrancy(tsd);
	}

	return addr;
}
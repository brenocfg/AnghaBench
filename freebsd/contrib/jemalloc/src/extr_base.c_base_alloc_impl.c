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
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * avail; } ;
typedef  TYPE_1__ base_t ;

/* Variables and functions */
 size_t ALIGNMENT_CEILING (size_t,size_t) ; 
 size_t NSIZES ; 
 size_t QUANTUM ; 
 size_t QUANTUM_CEILING (size_t) ; 
 int /*<<< orphan*/ * base_extent_alloc (int /*<<< orphan*/ *,TYPE_1__*,size_t,size_t) ; 
 void* base_extent_bump_alloc (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * extent_heap_remove_first (int /*<<< orphan*/ *) ; 
 size_t extent_sn_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sz_size2index (size_t) ; 

__attribute__((used)) static void *
base_alloc_impl(tsdn_t *tsdn, base_t *base, size_t size, size_t alignment,
    size_t *esn) {
	alignment = QUANTUM_CEILING(alignment);
	size_t usize = ALIGNMENT_CEILING(size, alignment);
	size_t asize = usize + alignment - QUANTUM;

	extent_t *extent = NULL;
	malloc_mutex_lock(tsdn, &base->mtx);
	for (szind_t i = sz_size2index(asize); i < NSIZES; i++) {
		extent = extent_heap_remove_first(&base->avail[i]);
		if (extent != NULL) {
			/* Use existing space. */
			break;
		}
	}
	if (extent == NULL) {
		/* Try to allocate more space. */
		extent = base_extent_alloc(tsdn, base, usize, alignment);
	}
	void *ret;
	if (extent == NULL) {
		ret = NULL;
		goto label_return;
	}

	ret = base_extent_bump_alloc(base, extent, usize, alignment);
	if (esn != NULL) {
		*esn = extent_sn_get(extent);
	}
label_return:
	malloc_mutex_unlock(tsdn, &base->mtx);
	return ret;
}
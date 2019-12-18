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
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t ALIGNMENT_CEILING (uintptr_t,size_t) ; 
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 int /*<<< orphan*/  ATOMIC_RELEASE ; 
 int /*<<< orphan*/ * EXTENT_HOOKS_INITIALIZER ; 
 int /*<<< orphan*/  EXTENT_NOT_HEAD ; 
 size_t PAGE ; 
 scalar_t__ PAGE_CEILING (uintptr_t) ; 
 int SC_NSIZES ; 
 int arena_extent_sn_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_load_b (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_b (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_p (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_exhausted ; 
 int /*<<< orphan*/  dss_max ; 
 int /*<<< orphan*/ * extent_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc_gap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dss_extending_finish () ; 
 int /*<<< orphan*/  extent_dss_extending_start () ; 
 void* extent_dss_max_update (void*) ; 
 void* extent_dss_sbrk (intptr_t) ; 
 int /*<<< orphan*/  extent_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,size_t,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ extent_purge_forced_wrapper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  extent_state_active ; 
 int /*<<< orphan*/  have_dss ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int pages_decommit (void*,size_t) ; 

void *
extent_alloc_dss(tsdn_t *tsdn, arena_t *arena, void *new_addr, size_t size,
    size_t alignment, bool *zero, bool *commit) {
	extent_t *gap;

	cassert(have_dss);
	assert(size > 0);
	assert(alignment == ALIGNMENT_CEILING(alignment, PAGE));

	/*
	 * sbrk() uses a signed increment argument, so take care not to
	 * interpret a large allocation request as a negative increment.
	 */
	if ((intptr_t)size < 0) {
		return NULL;
	}

	gap = extent_alloc(tsdn, arena);
	if (gap == NULL) {
		return NULL;
	}

	extent_dss_extending_start();
	if (!atomic_load_b(&dss_exhausted, ATOMIC_ACQUIRE)) {
		/*
		 * The loop is necessary to recover from races with other
		 * threads that are using the DSS for something other than
		 * malloc.
		 */
		while (true) {
			void *max_cur = extent_dss_max_update(new_addr);
			if (max_cur == NULL) {
				goto label_oom;
			}

			/*
			 * Compute how much page-aligned gap space (if any) is
			 * necessary to satisfy alignment.  This space can be
			 * recycled for later use.
			 */
			void *gap_addr_page = (void *)(PAGE_CEILING(
			    (uintptr_t)max_cur));
			void *ret = (void *)ALIGNMENT_CEILING(
			    (uintptr_t)gap_addr_page, alignment);
			size_t gap_size_page = (uintptr_t)ret -
			    (uintptr_t)gap_addr_page;
			if (gap_size_page != 0) {
				extent_init(gap, arena_ind_get(arena),
				    gap_addr_page, gap_size_page, false,
				    SC_NSIZES, arena_extent_sn_next(arena),
				    extent_state_active, false, true, true,
				    EXTENT_NOT_HEAD);
			}
			/*
			 * Compute the address just past the end of the desired
			 * allocation space.
			 */
			void *dss_next = (void *)((uintptr_t)ret + size);
			if ((uintptr_t)ret < (uintptr_t)max_cur ||
			    (uintptr_t)dss_next < (uintptr_t)max_cur) {
				goto label_oom; /* Wrap-around. */
			}
			/* Compute the increment, including subpage bytes. */
			void *gap_addr_subpage = max_cur;
			size_t gap_size_subpage = (uintptr_t)ret -
			    (uintptr_t)gap_addr_subpage;
			intptr_t incr = gap_size_subpage + size;

			assert((uintptr_t)max_cur + incr == (uintptr_t)ret +
			    size);

			/* Try to allocate. */
			void *dss_prev = extent_dss_sbrk(incr);
			if (dss_prev == max_cur) {
				/* Success. */
				atomic_store_p(&dss_max, dss_next,
				    ATOMIC_RELEASE);
				extent_dss_extending_finish();

				if (gap_size_page != 0) {
					extent_dalloc_gap(tsdn, arena, gap);
				} else {
					extent_dalloc(tsdn, arena, gap);
				}
				if (!*commit) {
					*commit = pages_decommit(ret, size);
				}
				if (*zero && *commit) {
					extent_hooks_t *extent_hooks =
					    EXTENT_HOOKS_INITIALIZER;
					extent_t extent;

					extent_init(&extent,
					    arena_ind_get(arena), ret, size,
					    size, false, SC_NSIZES,
					    extent_state_active, false, true,
					    true, EXTENT_NOT_HEAD);
					if (extent_purge_forced_wrapper(tsdn,
					    arena, &extent_hooks, &extent, 0,
					    size)) {
						memset(ret, 0, size);
					}
				}
				return ret;
			}
			/*
			 * Failure, whether due to OOM or a race with a raw
			 * sbrk() call from outside the allocator.
			 */
			if (dss_prev == (void *)-1) {
				/* OOM. */
				atomic_store_b(&dss_exhausted, true,
				    ATOMIC_RELEASE);
				goto label_oom;
			}
		}
	}
label_oom:
	extent_dss_extending_finish();
	extent_dalloc(tsdn, arena, gap);
	return NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_9__ {int /*<<< orphan*/ * arena; } ;
typedef  TYPE_2__ tcache_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_8__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_10__ {TYPE_1__ cur_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/ * arena_choose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* ipallocztm (int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_initialized () ; 
 size_t sz_sa2u (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tcache_arena_associate (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t tcache_bin_stack_alignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcache_init (int /*<<< orphan*/ *,TYPE_2__*,void*) ; 
 TYPE_4__* tcache_small_bin_get (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_stack_bytes ; 
 TYPE_2__* tsd_tcachep_get_unsafe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

bool
tsd_tcache_data_init(tsd_t *tsd) {
	tcache_t *tcache = tsd_tcachep_get_unsafe(tsd);
	assert(tcache_small_bin_get(tcache, 0)->cur_ptr.ptr == NULL);
	size_t alignment = tcache_bin_stack_alignment(total_stack_bytes);
	size_t size = sz_sa2u(total_stack_bytes, alignment);

	void *avail_array = ipallocztm(tsd_tsdn(tsd), size, alignment, true,
	    NULL, true, arena_get(TSDN_NULL, 0, true));
	if (avail_array == NULL) {
		return true;
	}

	tcache_init(tsd, tcache, avail_array);
	/*
	 * Initialization is a bit tricky here.  After malloc init is done, all
	 * threads can rely on arena_choose and associate tcache accordingly.
	 * However, the thread that does actual malloc bootstrapping relies on
	 * functional tsd, and it can only rely on a0.  In that case, we
	 * associate its tcache to a0 temporarily, and later on
	 * arena_choose_hard() will re-associate properly.
	 */
	tcache->arena = NULL;
	arena_t *arena;
	if (!malloc_initialized()) {
		/* If in initialization, assign to a0. */
		arena = arena_get(tsd_tsdn(tsd), 0, false);
		tcache_arena_associate(tsd_tsdn(tsd), tcache, arena);
	} else {
		arena = arena_choose(tsd, NULL);
		/* This may happen if thread.tcache.enabled is used. */
		if (tcache->arena == NULL) {
			tcache_arena_associate(tsd_tsdn(tsd), tcache, arena);
		}
	}
	assert(arena == tcache->arena);

	return false;
}
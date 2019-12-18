#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_2__ {size_t accumbytes; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t SC_LARGE_MINCLASS ; 
 int /*<<< orphan*/  atomic_compare_exchange_weak_u64 (size_t*,size_t*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t atomic_load_u64 (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ prof_idump_accumulated ; 

void
prof_idump_rollback_impl(tsdn_t *tsdn, size_t usize) {
	cassert(config_prof);

	/*
	 * Cancel out as much of the excessive accumbytes increase as possible
	 * without underflowing.  Interval-triggered dumps occur slightly more
	 * often than intended as a result of incomplete canceling.
	 */
	uint64_t a0, a1;
#ifdef JEMALLOC_ATOMIC_U64
	a0 = atomic_load_u64(&prof_idump_accumulated.accumbytes,
	    ATOMIC_RELAXED);
	do {
		a1 = (a0 >= SC_LARGE_MINCLASS - usize)
		    ? a0 - (SC_LARGE_MINCLASS - usize) : 0;
	} while (!atomic_compare_exchange_weak_u64(
	    &prof_idump_accumulated.accumbytes, &a0, a1, ATOMIC_RELAXED,
	    ATOMIC_RELAXED));
#else
	malloc_mutex_lock(tsdn, &prof_idump_accumulated.mtx);
	a0 = prof_idump_accumulated.accumbytes;
	a1 = (a0 >= SC_LARGE_MINCLASS - usize)
	    ?  a0 - (SC_LARGE_MINCLASS - usize) : 0;
	prof_idump_accumulated.accumbytes = a1;
	malloc_mutex_unlock(tsdn, &prof_idump_accumulated.mtx);
#endif
}
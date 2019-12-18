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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  accumbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_compare_exchange_weak_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_load_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ prof_idump_accumulated ; 
 int /*<<< orphan*/  prof_interval ; 

bool
prof_idump_accum_impl(tsdn_t *tsdn, uint64_t accumbytes) {
	cassert(config_prof);

	bool overflow;
	uint64_t a0, a1;

	/*
	 * If the application allocates fast enough (and/or if idump is slow
	 * enough), extreme overflow here (a1 >= prof_interval * 2) can cause
	 * idump trigger coalescing.  This is an intentional mechanism that
	 * avoids rate-limiting allocation.
	 */
#ifdef JEMALLOC_ATOMIC_U64
	a0 = atomic_load_u64(&prof_idump_accumulated.accumbytes,
	    ATOMIC_RELAXED);
	do {
		a1 = a0 + accumbytes;
		assert(a1 >= a0);
		overflow = (a1 >= prof_interval);
		if (overflow) {
			a1 %= prof_interval;
		}
	} while (!atomic_compare_exchange_weak_u64(
	    &prof_idump_accumulated.accumbytes, &a0, a1, ATOMIC_RELAXED,
	    ATOMIC_RELAXED));
#else
	malloc_mutex_lock(tsdn, &prof_idump_accumulated.mtx);
	a0 = prof_idump_accumulated.accumbytes;
	a1 = a0 + accumbytes;
	overflow = (a1 >= prof_interval);
	if (overflow) {
		a1 %= prof_interval;
	}
	prof_idump_accumulated.accumbytes = a1;
	malloc_mutex_unlock(tsdn, &prof_idump_accumulated.mtx);
#endif
	return overflow;
}
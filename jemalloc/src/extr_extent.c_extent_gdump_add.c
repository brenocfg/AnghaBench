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

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  atomic_compare_exchange_weak_zu (int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t atomic_fetch_add_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  curpages ; 
 size_t extent_size_get (int /*<<< orphan*/  const*) ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  highpages ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_gdump (int /*<<< orphan*/ *) ; 
 scalar_t__ prof_gdump_get_unlocked () ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extent_gdump_add(tsdn_t *tsdn, const extent_t *extent) {
	cassert(config_prof);
	/* prof_gdump() requirement. */
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	if (opt_prof && extent_state_get(extent) == extent_state_active) {
		size_t nadd = extent_size_get(extent) >> LG_PAGE;
		size_t cur = atomic_fetch_add_zu(&curpages, nadd,
		    ATOMIC_RELAXED) + nadd;
		size_t high = atomic_load_zu(&highpages, ATOMIC_RELAXED);
		while (cur > high && !atomic_compare_exchange_weak_zu(
		    &highpages, &high, cur, ATOMIC_RELAXED, ATOMIC_RELAXED)) {
			/*
			 * Don't refresh cur, because it may have decreased
			 * since this thread lost the highpages update race.
			 * Note that high is updated in case of CAS failure.
			 */
		}
		if (cur > high && prof_gdump_get_unlocked()) {
			prof_gdump(tsdn);
		}
	}
}
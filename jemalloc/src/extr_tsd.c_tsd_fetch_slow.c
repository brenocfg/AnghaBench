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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_tsd_data_cleanup_done (int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_booted ; 
 int /*<<< orphan*/  tsd_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_data_init_nocleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_fast (int /*<<< orphan*/ *) ; 
 int* tsd_reentrancy_levelp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_slow_update (int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_state_minimal_initialized ; 
 scalar_t__ tsd_state_nominal ; 
 scalar_t__ tsd_state_nominal_recompute ; 
 scalar_t__ tsd_state_nominal_slow ; 
 scalar_t__ tsd_state_purgatory ; 
 scalar_t__ tsd_state_reincarnated ; 
 int /*<<< orphan*/  tsd_state_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ tsd_state_uninitialized ; 

tsd_t *
tsd_fetch_slow(tsd_t *tsd, bool minimal) {
	assert(!tsd_fast(tsd));

	if (tsd_state_get(tsd) == tsd_state_nominal_slow) {
		/*
		 * On slow path but no work needed.  Note that we can't
		 * necessarily *assert* that we're slow, because we might be
		 * slow because of an asynchronous modification to global state,
		 * which might be asynchronously modified *back*.
		 */
	} else if (tsd_state_get(tsd) == tsd_state_nominal_recompute) {
		tsd_slow_update(tsd);
	} else if (tsd_state_get(tsd) == tsd_state_uninitialized) {
		if (!minimal) {
			if (tsd_booted) {
				tsd_state_set(tsd, tsd_state_nominal);
				tsd_slow_update(tsd);
				/* Trigger cleanup handler registration. */
				tsd_set(tsd);
				tsd_data_init(tsd);
			}
		} else {
			tsd_state_set(tsd, tsd_state_minimal_initialized);
			tsd_set(tsd);
			tsd_data_init_nocleanup(tsd);
		}
	} else if (tsd_state_get(tsd) == tsd_state_minimal_initialized) {
		if (!minimal) {
			/* Switch to fully initialized. */
			tsd_state_set(tsd, tsd_state_nominal);
			assert(*tsd_reentrancy_levelp_get(tsd) >= 1);
			(*tsd_reentrancy_levelp_get(tsd))--;
			tsd_slow_update(tsd);
			tsd_data_init(tsd);
		} else {
			assert_tsd_data_cleanup_done(tsd);
		}
	} else if (tsd_state_get(tsd) == tsd_state_purgatory) {
		tsd_state_set(tsd, tsd_state_reincarnated);
		tsd_set(tsd);
		tsd_data_init_nocleanup(tsd);
	} else {
		assert(tsd_state_get(tsd) == tsd_state_reincarnated);
	}

	return tsd;
}
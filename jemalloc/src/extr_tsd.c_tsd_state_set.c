#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tsd_add_nominal (TYPE_1__*) ; 
 scalar_t__ tsd_atomic_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_atomic_store (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int tsd_in_nominal_list (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_remove_nominal (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_slow_update (TYPE_1__*) ; 
 scalar_t__ tsd_state_nominal_max ; 
 scalar_t__ tsd_state_nominal_recompute ; 

void
tsd_state_set(tsd_t *tsd, uint8_t new_state) {
	/* Only the tsd module can change the state *to* recompute. */
	assert(new_state != tsd_state_nominal_recompute);
	uint8_t old_state = tsd_atomic_load(&tsd->state, ATOMIC_RELAXED);
	if (old_state > tsd_state_nominal_max) {
		/*
		 * Not currently in the nominal list, but it might need to be
		 * inserted there.
		 */
		assert(!tsd_in_nominal_list(tsd));
		tsd_atomic_store(&tsd->state, new_state, ATOMIC_RELAXED);
		if (new_state <= tsd_state_nominal_max) {
			tsd_add_nominal(tsd);
		}
	} else {
		/*
		 * We're currently nominal.  If the new state is non-nominal,
		 * great; we take ourselves off the list and just enter the new
		 * state.
		 */
		assert(tsd_in_nominal_list(tsd));
		if (new_state > tsd_state_nominal_max) {
			tsd_remove_nominal(tsd);
			tsd_atomic_store(&tsd->state, new_state,
			    ATOMIC_RELAXED);
		} else {
			/*
			 * This is the tricky case.  We're transitioning from
			 * one nominal state to another.  The caller can't know
			 * about any races that are occuring at the same time,
			 * so we always have to recompute no matter what.
			 */
			tsd_slow_update(tsd);
		}
	}
}
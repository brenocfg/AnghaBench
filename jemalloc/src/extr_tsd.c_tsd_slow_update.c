#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 scalar_t__ tsd_atomic_exchange (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tsd_state_compute (TYPE_1__*) ; 
 scalar_t__ tsd_state_nominal_recompute ; 

void
tsd_slow_update(tsd_t *tsd) {
	uint8_t old_state;
	do {
		uint8_t new_state = tsd_state_compute(tsd);
		old_state = tsd_atomic_exchange(&tsd->state, new_state,
		    ATOMIC_ACQUIRE);
	} while (old_state == tsd_state_nominal_recompute);
}
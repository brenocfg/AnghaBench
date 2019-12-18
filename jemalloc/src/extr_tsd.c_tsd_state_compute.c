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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 scalar_t__ malloc_slow ; 
 scalar_t__ tsd_global_slow () ; 
 scalar_t__ tsd_local_slow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_nominal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_state_nominal ; 
 int /*<<< orphan*/  tsd_state_nominal_slow ; 

__attribute__((used)) static uint8_t
tsd_state_compute(tsd_t *tsd) {
	if (!tsd_nominal(tsd)) {
		return tsd_state_get(tsd);
	}
	/* We're in *a* nominal state; but which one? */
	if (malloc_slow || tsd_local_slow(tsd) || tsd_global_slow()) {
		return tsd_state_nominal_slow;
	} else {
		return tsd_state_nominal;
	}
}
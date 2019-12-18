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
 int /*<<< orphan*/  malloc_mutex_postfork_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_add_nominal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_nominal_tsds ; 
 int /*<<< orphan*/  tsd_nominal_tsds_lock ; 
 scalar_t__ tsd_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_state_nominal_max ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
tsd_postfork_child(tsd_t *tsd) {
	malloc_mutex_postfork_child(tsd_tsdn(tsd), &tsd_nominal_tsds_lock);
	ql_new(&tsd_nominal_tsds);

	if (tsd_state_get(tsd) <= tsd_state_nominal_max) {
		tsd_add_nominal(tsd);
	}
}
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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_2__ {int /*<<< orphan*/  tsd_link; } ;

/* Variables and functions */
 TYPE_1__ TSD_MANGLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcache ; 
 int tsd_in_nominal_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_nominal_tsds ; 
 int /*<<< orphan*/  tsd_nominal_tsds_lock ; 
 scalar_t__ tsd_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_state_nominal_max ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tsd_remove_nominal(tsd_t *tsd) {
	assert(tsd_in_nominal_list(tsd));
	assert(tsd_state_get(tsd) <= tsd_state_nominal_max);
	malloc_mutex_lock(tsd_tsdn(tsd), &tsd_nominal_tsds_lock);
	ql_remove(&tsd_nominal_tsds, tsd, TSD_MANGLE(tcache).tsd_link);
	malloc_mutex_unlock(tsd_tsdn(tsd), &tsd_nominal_tsds_lock);
}
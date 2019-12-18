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

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  atomic_fetch_add_u32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_force_recompute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_global_slow_count ; 

void
tsd_global_slow_inc(tsdn_t *tsdn) {
	atomic_fetch_add_u32(&tsd_global_slow_count, 1, ATOMIC_RELAXED);
	/*
	 * We unconditionally force a recompute, even if the global slow count
	 * was already positive.  If we didn't, then it would be possible for us
	 * to return to the user, have the user synchronize externally with some
	 * other thread, and then have that other thread not have picked up the
	 * update yet (since the original incrementing thread might still be
	 * making its way through the tsd list).
	 */
	tsd_force_recompute(tsdn);
}
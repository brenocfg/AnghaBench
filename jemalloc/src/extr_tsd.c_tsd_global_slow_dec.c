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
 int /*<<< orphan*/  atomic_fetch_sub_u32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_force_recompute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_global_slow_count ; 

void tsd_global_slow_dec(tsdn_t *tsdn) {
	atomic_fetch_sub_u32(&tsd_global_slow_count, 1, ATOMIC_RELAXED);
	/* See the note in ..._inc(). */
	tsd_force_recompute(tsdn);
}
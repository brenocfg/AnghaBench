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

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int rushjob ; 
 int stat_rush_requests ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  sync_wakeup ; 
 int syncdelay ; 

int
speedup_syncer(void)
{
	int ret = 0;

	mtx_lock(&sync_mtx);
	if (rushjob < syncdelay / 2) {
		rushjob += 1;
		stat_rush_requests += 1;
		ret = 1;
	}
	mtx_unlock(&sync_mtx);
	cv_broadcast(&sync_wakeup);
	return (ret);
}
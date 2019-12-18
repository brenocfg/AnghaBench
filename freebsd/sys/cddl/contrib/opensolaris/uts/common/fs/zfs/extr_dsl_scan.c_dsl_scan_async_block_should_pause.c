#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {scalar_t__ scn_visited_this_txg; int scn_sync_start_time; scalar_t__ scn_async_block_min_time_ms; TYPE_2__* scn_dp; } ;
typedef  TYPE_1__ dsl_scan_t ;
typedef  int boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 int NANOSEC ; 
 scalar_t__ NSEC2MSEC (int) ; 
 int gethrtime () ; 
 scalar_t__ spa_shutting_down (int /*<<< orphan*/ ) ; 
 scalar_t__ txg_sync_waiting (TYPE_2__*) ; 
 scalar_t__ zfs_async_block_max_blocks ; 
 scalar_t__ zfs_recover ; 
 int zfs_txg_timeout ; 

__attribute__((used)) static boolean_t
dsl_scan_async_block_should_pause(dsl_scan_t *scn)
{
	uint64_t elapsed_nanosecs;

	if (zfs_recover)
		return (B_FALSE);

	if (scn->scn_visited_this_txg >= zfs_async_block_max_blocks)
		return (B_TRUE);

	elapsed_nanosecs = gethrtime() - scn->scn_sync_start_time;
	return (elapsed_nanosecs / NANOSEC > zfs_txg_timeout ||
	    (NSEC2MSEC(elapsed_nanosecs) > scn->scn_async_block_min_time_ms &&
	    txg_sync_waiting(scn->scn_dp)) ||
	    spa_shutting_down(scn->scn_dp->dp_spa));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ zc_flags; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  POOL_SCAN_NONE ; 
 scalar_t__ POOL_SCRUB_FLAGS_END ; 
 scalar_t__ POOL_SCRUB_PAUSE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int spa_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_scan_stop (int /*<<< orphan*/ *) ; 
 int spa_scrub_pause_resume (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
zfs_ioc_pool_scan(zfs_cmd_t *zc)
{
	spa_t *spa;
	int error;

	if ((error = spa_open(zc->zc_name, &spa, FTAG)) != 0)
		return (error);

	if (zc->zc_flags >= POOL_SCRUB_FLAGS_END)
		return (SET_ERROR(EINVAL));

	if (zc->zc_flags == POOL_SCRUB_PAUSE)
		error = spa_scrub_pause_resume(spa, POOL_SCRUB_PAUSE);
	else if (zc->zc_cookie == POOL_SCAN_NONE)
		error = spa_scan_stop(spa);
	else
		error = spa_scan(spa, zc->zc_cookie);

	spa_close(spa, FTAG);

	return (error);
}
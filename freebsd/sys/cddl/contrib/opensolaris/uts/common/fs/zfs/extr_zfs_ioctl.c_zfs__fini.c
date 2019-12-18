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
 int EBUSY ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_tsd_key ; 
 scalar_t__ spa_busy () ; 
 int /*<<< orphan*/  spa_fini () ; 
 int /*<<< orphan*/  tsd_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_allow_log_key ; 
 scalar_t__ zfs_busy () ; 
 int /*<<< orphan*/  zfs_fini () ; 
 int /*<<< orphan*/  zfs_fsyncer_key ; 
 int /*<<< orphan*/  zfs_share_lock ; 
 int /*<<< orphan*/  zfsdev_fini () ; 
 scalar_t__ zio_injection_enabled ; 
 scalar_t__ zvol_busy () ; 
 int /*<<< orphan*/  zvol_fini () ; 

int
zfs__fini(void)
{
	if (spa_busy() || zfs_busy() || zvol_busy() ||
	    zio_injection_enabled) {
		return (EBUSY);
	}

	zfsdev_fini();
	zvol_fini();
	zfs_fini();
	spa_fini();

	tsd_destroy(&zfs_fsyncer_key);
	tsd_destroy(&rrw_tsd_key);
	tsd_destroy(&zfs_allow_log_key);

	mutex_destroy(&zfs_share_lock);

	return (0);
}
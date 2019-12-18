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
typedef  int /*<<< orphan*/  zfs_soft_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_LOG (int,char*) ; 
 scalar_t__ ddi_soft_state_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsdev_state ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 

void
zvol_init(void)
{
	VERIFY(ddi_soft_state_init(&zfsdev_state, sizeof (zfs_soft_state_t),
	    1) == 0);
#ifdef illumos
	mutex_init(&zfsdev_state_lock, NULL, MUTEX_DEFAULT, NULL);
#else
	ZFS_LOG(1, "ZVOL Initialized.");
#endif
}
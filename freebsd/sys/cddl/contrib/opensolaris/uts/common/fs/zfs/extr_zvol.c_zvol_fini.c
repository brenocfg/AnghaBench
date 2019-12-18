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
 int /*<<< orphan*/  ZFS_LOG (int,char*) ; 
 int /*<<< orphan*/  ddi_soft_state_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsdev_state ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 

void
zvol_fini(void)
{
#ifdef illumos
	mutex_destroy(&zfsdev_state_lock);
#endif
	ddi_soft_state_fini(&zfsdev_state);
	ZFS_LOG(1, "ZVOL Deinitialized.");
}
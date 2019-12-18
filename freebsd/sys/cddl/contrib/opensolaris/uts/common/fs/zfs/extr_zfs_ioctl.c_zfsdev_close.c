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
typedef  int /*<<< orphan*/  zfs_onexit_t ;
typedef  scalar_t__ minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZSST_CTLDEV ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  zfs_ctldev_destroy (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * zfsdev_get_soft_state (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zfsdev_close(void *data)
{
	zfs_onexit_t *zo;
	minor_t minor = (minor_t)(uintptr_t)data;

	if (minor == 0)
		return;

	mutex_enter(&spa_namespace_lock);
	zo = zfsdev_get_soft_state(minor, ZSST_CTLDEV);
	if (zo == NULL) {
		mutex_exit(&spa_namespace_lock);
		return;
	}
	zfs_ctldev_destroy(zo, minor);
	mutex_exit(&spa_namespace_lock);
}
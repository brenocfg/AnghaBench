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
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddi_soft_state_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  zfs_onexit_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsdev_state ; 

__attribute__((used)) static void
zfs_ctldev_destroy(zfs_onexit_t *zo, minor_t minor)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	zfs_onexit_destroy(zo);
	ddi_soft_state_free(zfsdev_state, minor);
}
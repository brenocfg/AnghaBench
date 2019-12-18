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
struct TYPE_3__ {int zss_type; void* zss_data; } ;
typedef  TYPE_1__ zfs_soft_state_t ;
typedef  int /*<<< orphan*/  minor_t ;
typedef  enum zfs_soft_state_type { ____Placeholder_zfs_soft_state_type } zfs_soft_state_type ;

/* Variables and functions */
 TYPE_1__* ddi_get_soft_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsdev_state ; 

void *
zfsdev_get_soft_state(minor_t minor, enum zfs_soft_state_type which)
{
	zfs_soft_state_t *zp;

	zp = ddi_get_soft_state(zfsdev_state, minor);
	if (zp == NULL || zp->zss_type != which)
		return (NULL);

	return (zp->zss_data);
}
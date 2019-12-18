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
struct TYPE_3__ {int /*<<< orphan*/  zss_data; int /*<<< orphan*/  zss_type; } ;
typedef  TYPE_1__ zfs_soft_state_t ;
typedef  int /*<<< orphan*/  zfs_onexit_t ;
struct cdev {int dummy; } ;
typedef  scalar_t__ minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ DDI_SUCCESS ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSST_CTLDEV ; 
 TYPE_1__* ddi_get_soft_state (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ddi_soft_state_zalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  zfs_onexit_init (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfsdev_close ; 
 scalar_t__ zfsdev_minor_alloc () ; 
 int /*<<< orphan*/  zfsdev_state ; 

__attribute__((used)) static int
zfs_ctldev_init(struct cdev *devp)
{
	minor_t minor;
	zfs_soft_state_t *zs;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	minor = zfsdev_minor_alloc();
	if (minor == 0)
		return (SET_ERROR(ENXIO));

	if (ddi_soft_state_zalloc(zfsdev_state, minor) != DDI_SUCCESS)
		return (SET_ERROR(EAGAIN));

	devfs_set_cdevpriv((void *)(uintptr_t)minor, zfsdev_close);

	zs = ddi_get_soft_state(zfsdev_state, minor);
	zs->zss_type = ZSST_CTLDEV;
	zfs_onexit_init((zfs_onexit_t **)&zs->zss_data);

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zv_minor; scalar_t__ zv_total_opens; scalar_t__ zv_volmode; int /*<<< orphan*/  zv_rangelock; int /*<<< orphan*/ * zv_dev; int /*<<< orphan*/  zv_name; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  int /*<<< orphan*/  nmbuf ;
typedef  int minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_LOG (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ZFS_VOLMODE_DEV ; 
 scalar_t__ ZFS_VOLMODE_GEOM ; 
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ddi_soft_state_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rangelock_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  zfs_dip ; 
 int /*<<< orphan*/  zfsdev_state ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/  zv_links ; 
 int /*<<< orphan*/  zvol_geom_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_minors ; 

__attribute__((used)) static int
zvol_remove_zv(zvol_state_t *zv)
{
#ifdef illumos
	char nmbuf[20];
	minor_t minor = zv->zv_minor;
#endif

	ASSERT(MUTEX_HELD(&zfsdev_state_lock));
	if (zv->zv_total_opens != 0)
		return (SET_ERROR(EBUSY));

#ifdef illumos
	(void) snprintf(nmbuf, sizeof (nmbuf), "%u,raw", minor);
	ddi_remove_minor_node(zfs_dip, nmbuf);

	(void) snprintf(nmbuf, sizeof (nmbuf), "%u", minor);
	ddi_remove_minor_node(zfs_dip, nmbuf);
#else
	ZFS_LOG(1, "ZVOL %s destroyed.", zv->zv_name);

	LIST_REMOVE(zv, zv_links);
	if (zv->zv_volmode == ZFS_VOLMODE_GEOM) {
		g_topology_lock();
		zvol_geom_destroy(zv);
		g_topology_unlock();
	} else if (zv->zv_volmode == ZFS_VOLMODE_DEV) {
		if (zv->zv_dev != NULL)
			destroy_dev(zv->zv_dev);
	}
#endif

	rangelock_fini(&zv->zv_rangelock);

	kmem_free(zv, sizeof (zvol_state_t));
#ifdef illumos
	ddi_soft_state_free(zfsdev_state, minor);
#endif
	zvol_minors--;
	return (0);
}
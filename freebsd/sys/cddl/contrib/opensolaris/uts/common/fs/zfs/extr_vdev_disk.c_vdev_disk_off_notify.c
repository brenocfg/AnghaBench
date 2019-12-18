#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vdev_spa; void* vdev_remove_wanted; TYPE_2__* vdev_tsd; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_6__ {void* vd_ldi_offline; } ;
typedef  TYPE_2__ vdev_disk_t ;
typedef  int /*<<< orphan*/  ldi_handle_t ;
typedef  int /*<<< orphan*/  ldi_ev_cookie_t ;

/* Variables and functions */
 void* B_TRUE ; 
 int /*<<< orphan*/  LDI_EV_OFFLINE ; 
 int LDI_EV_SUCCESS ; 
 int /*<<< orphan*/  SPA_ASYNC_REMOVE ; 
 int /*<<< orphan*/  ldi_ev_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_disk_close (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_post_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
vdev_disk_off_notify(ldi_handle_t lh, ldi_ev_cookie_t ecookie, void *arg,
    void *ev_data)
{
	vdev_t *vd = (vdev_t *)arg;
	vdev_disk_t *dvd = vd->vdev_tsd;

	/*
	 * Ignore events other than offline.
	 */
	if (strcmp(ldi_ev_get_type(ecookie), LDI_EV_OFFLINE) != 0)
		return (LDI_EV_SUCCESS);

	/*
	 * All LDI handles must be closed for the state change to succeed, so
	 * call on vdev_disk_close() to do this.
	 *
	 * We inform vdev_disk_close that it is being called from offline
	 * notify context so it will defer cleanup of LDI event callbacks and
	 * freeing of vd->vdev_tsd to the offline finalize or a reopen.
	 */
	dvd->vd_ldi_offline = B_TRUE;
	vdev_disk_close(vd);

	/*
	 * Now that the device is closed, request that the spa_async_thread
	 * mark the device as REMOVED and notify FMA of the removal.
	 */
	zfs_post_remove(vd->vdev_spa, vd);
	vd->vdev_remove_wanted = B_TRUE;
	spa_async_request(vd->vdev_spa, SPA_ASYNC_REMOVE);

	return (LDI_EV_SUCCESS);
}
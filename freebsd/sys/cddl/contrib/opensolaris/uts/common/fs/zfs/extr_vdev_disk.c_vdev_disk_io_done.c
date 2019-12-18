#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ io_error; int /*<<< orphan*/  io_spa; TYPE_2__* io_vd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_7__ {void* vdev_delayed_close; void* vdev_remove_wanted; TYPE_3__* vdev_tsd; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_8__ {int /*<<< orphan*/  vd_lh; } ;
typedef  TYPE_3__ vdev_disk_t ;

/* Variables and functions */
 void* B_TRUE ; 
 int /*<<< orphan*/  DKIOCSTATE ; 
 int DKIO_INSERTED ; 
 int DKIO_NONE ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  FKIOCTL ; 
 int /*<<< orphan*/  SPA_ASYNC_REMOVE ; 
 int /*<<< orphan*/  kcred ; 
 scalar_t__ ldi_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_post_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
vdev_disk_io_done(zio_t *zio)
{
	vdev_t *vd = zio->io_vd;

	/*
	 * If the device returned EIO, then attempt a DKIOCSTATE ioctl to see if
	 * the device has been removed.  If this is the case, then we trigger an
	 * asynchronous removal of the device. Otherwise, probe the device and
	 * make sure it's still accessible.
	 */
	if (zio->io_error == EIO && !vd->vdev_remove_wanted) {
		vdev_disk_t *dvd = vd->vdev_tsd;
		int state = DKIO_NONE;

		if (ldi_ioctl(dvd->vd_lh, DKIOCSTATE, (intptr_t)&state,
		    FKIOCTL, kcred, NULL) == 0 && state != DKIO_INSERTED) {
			/*
			 * We post the resource as soon as possible, instead of
			 * when the async removal actually happens, because the
			 * DE is using this information to discard previous I/O
			 * errors.
			 */
			zfs_post_remove(zio->io_spa, vd);
			vd->vdev_remove_wanted = B_TRUE;
			spa_async_request(zio->io_spa, SPA_ASYNC_REMOVE);
		} else if (!vd->vdev_delayed_close) {
			vd->vdev_delayed_close = B_TRUE;
		}
	}
}
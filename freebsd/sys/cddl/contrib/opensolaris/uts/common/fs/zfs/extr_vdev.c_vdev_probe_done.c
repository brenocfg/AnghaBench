#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ io_type; scalar_t__ io_error; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_offset; TYPE_3__* io_private; TYPE_2__* io_vd; int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zio_link_t ;
struct TYPE_19__ {int vdev_cant_read; int vdev_cant_write; int /*<<< orphan*/  vdev_probe_lock; TYPE_1__* vdev_probe_zio; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_20__ {int vps_readable; int vps_writeable; int /*<<< orphan*/  vps_flags; } ;
typedef  TYPE_3__ vdev_probe_stats_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_PROBE_FAILURE ; 
 void* SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_OFF ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_WRITE ; 
 scalar_t__ ZIO_TYPE_NULL ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_accessible (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_dbgmsg (TYPE_2__*,char*) ; 
 scalar_t__ vdev_readable (TYPE_2__*) ; 
 scalar_t__ vdev_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_ereport_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 TYPE_1__* zio_walk_parents (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zio_write_phys (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (TYPE_1__*),TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_probe_done(zio_t *zio)
{
	spa_t *spa = zio->io_spa;
	vdev_t *vd = zio->io_vd;
	vdev_probe_stats_t *vps = zio->io_private;

	ASSERT(vd->vdev_probe_zio != NULL);

	if (zio->io_type == ZIO_TYPE_READ) {
		if (zio->io_error == 0)
			vps->vps_readable = 1;
		if (zio->io_error == 0 && spa_writeable(spa)) {
			zio_nowait(zio_write_phys(vd->vdev_probe_zio, vd,
			    zio->io_offset, zio->io_size, zio->io_abd,
			    ZIO_CHECKSUM_OFF, vdev_probe_done, vps,
			    ZIO_PRIORITY_SYNC_WRITE, vps->vps_flags, B_TRUE));
		} else {
			abd_free(zio->io_abd);
		}
	} else if (zio->io_type == ZIO_TYPE_WRITE) {
		if (zio->io_error == 0)
			vps->vps_writeable = 1;
		abd_free(zio->io_abd);
	} else if (zio->io_type == ZIO_TYPE_NULL) {
		zio_t *pio;

		vd->vdev_cant_read |= !vps->vps_readable;
		vd->vdev_cant_write |= !vps->vps_writeable;

		if (vdev_readable(vd) &&
		    (vdev_writeable(vd) || !spa_writeable(spa))) {
			zio->io_error = 0;
		} else {
			ASSERT(zio->io_error != 0);
			vdev_dbgmsg(vd, "failed probe");
			zfs_ereport_post(FM_EREPORT_ZFS_PROBE_FAILURE,
			    spa, vd, NULL, 0, 0);
			zio->io_error = SET_ERROR(ENXIO);
		}

		mutex_enter(&vd->vdev_probe_lock);
		ASSERT(vd->vdev_probe_zio == zio);
		vd->vdev_probe_zio = NULL;
		mutex_exit(&vd->vdev_probe_lock);

		zio_link_t *zl = NULL;
		while ((pio = zio_walk_parents(zio, &zl)) != NULL)
			if (!vdev_accessible(vd, pio))
				pio->io_error = SET_ERROR(ENXIO);

		kmem_free(vps, sizeof (*vps));
	}
}
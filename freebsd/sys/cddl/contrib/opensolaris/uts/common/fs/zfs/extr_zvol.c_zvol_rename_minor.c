#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zv_volmode; scalar_t__ zv_total_opens; int /*<<< orphan*/  zv_name; struct cdev* zv_dev; int /*<<< orphan*/  zv_flags; struct g_provider* zv_provider; int /*<<< orphan*/  zv_volsize; } ;
typedef  TYPE_1__ zvol_state_t ;
struct make_dev_args {int mda_flags; int mda_mode; TYPE_1__* mda_si_drv2; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_cr; int /*<<< orphan*/ * mda_devsw; } ;
struct g_provider {int flags; TYPE_1__* private; int /*<<< orphan*/  mediasize; int /*<<< orphan*/  sectorsize; struct g_geom* geom; } ;
struct g_geom {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_iosize_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int G_PF_DIRECT_RECEIVE ; 
 int G_PF_DIRECT_SEND ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ ZFS_VOLMODE_DEV ; 
 scalar_t__ ZFS_VOLMODE_GEOM ; 
 int /*<<< orphan*/  ZVOL_DRIVER ; 
 int /*<<< orphan*/  ZVOL_EXCL ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_wither_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 scalar_t__ make_dev_s (struct make_dev_args*,struct cdev**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/  zvol_cdevsw ; 
 int /*<<< orphan*/  zvol_last_close (TYPE_1__*) ; 

__attribute__((used)) static void
zvol_rename_minor(zvol_state_t *zv, const char *newname)
{
	struct g_geom *gp;
	struct g_provider *pp;
	struct cdev *dev;

	ASSERT(MUTEX_HELD(&zfsdev_state_lock));

	if (zv->zv_volmode == ZFS_VOLMODE_GEOM) {
		g_topology_lock();
		pp = zv->zv_provider;
		ASSERT(pp != NULL);
		gp = pp->geom;
		ASSERT(gp != NULL);

		zv->zv_provider = NULL;
		g_wither_provider(pp, ENXIO);

		pp = g_new_providerf(gp, "%s/%s", ZVOL_DRIVER, newname);
		pp->flags |= G_PF_DIRECT_RECEIVE | G_PF_DIRECT_SEND;
		pp->sectorsize = DEV_BSIZE;
		pp->mediasize = zv->zv_volsize;
		pp->private = zv;
		zv->zv_provider = pp;
		g_error_provider(pp, 0);
		g_topology_unlock();
	} else if (zv->zv_volmode == ZFS_VOLMODE_DEV) {
		struct make_dev_args args;

		if ((dev = zv->zv_dev) != NULL) {
			zv->zv_dev = NULL;
			destroy_dev(dev);
			if (zv->zv_total_opens > 0) {
				zv->zv_flags &= ~ZVOL_EXCL;
				zv->zv_total_opens = 0;
				zvol_last_close(zv);
			}
		}

		make_dev_args_init(&args);
		args.mda_flags = MAKEDEV_CHECKNAME | MAKEDEV_WAITOK;
		args.mda_devsw = &zvol_cdevsw;
		args.mda_cr = NULL;
		args.mda_uid = UID_ROOT;
		args.mda_gid = GID_OPERATOR;
		args.mda_mode = 0640;
		args.mda_si_drv2 = zv;
		if (make_dev_s(&args, &zv->zv_dev,
		    "%s/%s", ZVOL_DRIVER, newname) == 0)
			zv->zv_dev->si_iosize_max = MAXPHYS;
	}
	strlcpy(zv->zv_name, newname, sizeof(zv->zv_name));
}
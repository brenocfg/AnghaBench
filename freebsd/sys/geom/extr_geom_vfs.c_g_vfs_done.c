#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; struct mount* v_mount; struct cdev* v_rdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  f_syncwrites; int /*<<< orphan*/  f_asyncwrites; int /*<<< orphan*/  f_syncreads; int /*<<< orphan*/  f_asyncreads; } ;
struct mount {TYPE_3__ mnt_stat; } ;
struct g_vfs_softc {scalar_t__ sc_active; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_orphaned; } ;
struct g_consumer {TYPE_4__* geom; } ;
struct cdev {struct mount* si_mountpt; TYPE_1__* si_devsw; } ;
struct TYPE_6__ {int /*<<< orphan*/  lk_lock; } ;
struct buf {scalar_t__ b_iocmd; scalar_t__ b_bcount; scalar_t__ b_resid; int /*<<< orphan*/  b_ioflags; scalar_t__ b_error; TYPE_2__ b_lock; struct vnode* b_vp; } ;
struct bio {scalar_t__ bio_completed; scalar_t__ bio_error; int /*<<< orphan*/  bio_flags; struct g_consumer* bio_from; struct buf* bio_caller2; } ;
struct TYPE_8__ {struct g_vfs_softc* softc; } ;
struct TYPE_5__ {int d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int D_DISK ; 
 scalar_t__ LK_HOLDER (int /*<<< orphan*/ ) ; 
 scalar_t__ LK_KERNPROC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_print_bio (char*,struct bio*,char*,scalar_t__) ; 
 int /*<<< orphan*/  g_vfs_destroy ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_vfs_done(struct bio *bip)
{
	struct g_consumer *cp;
	struct g_vfs_softc *sc;
	struct buf *bp;
	int destroy;
	struct mount *mp;
	struct vnode *vp;
	struct cdev *cdevp;

	/*
	 * Collect statistics on synchronous and asynchronous read
	 * and write counts for disks that have associated filesystems.
	 */
	bp = bip->bio_caller2;
	vp = bp->b_vp;
	if (vp != NULL) {
		/*
		 * If not a disk vnode, use its associated mount point
		 * otherwise use the mountpoint associated with the disk.
		 */
		VI_LOCK(vp);
		if (vp->v_type != VCHR ||
		    (cdevp = vp->v_rdev) == NULL ||
		    cdevp->si_devsw == NULL ||
		    (cdevp->si_devsw->d_flags & D_DISK) == 0)
			mp = vp->v_mount;
		else
			mp = cdevp->si_mountpt;
		if (mp != NULL) {
			if (bp->b_iocmd == BIO_READ) {
				if (LK_HOLDER(bp->b_lock.lk_lock) == LK_KERNPROC)
					mp->mnt_stat.f_asyncreads++;
				else
					mp->mnt_stat.f_syncreads++;
			} else if (bp->b_iocmd == BIO_WRITE) {
				if (LK_HOLDER(bp->b_lock.lk_lock) == LK_KERNPROC)
					mp->mnt_stat.f_asyncwrites++;
				else
					mp->mnt_stat.f_syncwrites++;
			}
		}
		VI_UNLOCK(vp);
	}

	cp = bip->bio_from;
	sc = cp->geom->softc;
	if (bip->bio_error)
		g_print_bio("g_vfs_done():", bip, "error = %d",
		    bip->bio_error);
	bp->b_error = bip->bio_error;
	bp->b_ioflags = bip->bio_flags;
	if (bip->bio_error)
		bp->b_ioflags |= BIO_ERROR;
	bp->b_resid = bp->b_bcount - bip->bio_completed;
	g_destroy_bio(bip);

	mtx_lock(&sc->sc_mtx);
	destroy = ((--sc->sc_active) == 0 && sc->sc_orphaned);
	mtx_unlock(&sc->sc_mtx);
	if (destroy)
		g_post_event(g_vfs_destroy, cp, M_WAITOK, NULL);

	bufdone(bp);
}
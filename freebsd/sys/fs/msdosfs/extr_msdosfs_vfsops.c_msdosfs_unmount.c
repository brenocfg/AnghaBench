#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bv_hd; } ;
struct TYPE_7__ {int /*<<< orphan*/  bv_hd; } ;
struct bufobj {int /*<<< orphan*/  bo_numoutput; TYPE_3__ bo_dirty; TYPE_2__ bo_clean; } ;
struct TYPE_6__ {int /*<<< orphan*/  tqe_prev; } ;
struct vnode {int /*<<< orphan*/  v_type; struct bufobj v_bufobj; int /*<<< orphan*/  v_mount; TYPE_1__ v_actfreelist; } ;
struct msdosfsmount {int pm_flags; int /*<<< orphan*/  pm_fatlock; struct msdosfsmount* pm_inusemap; TYPE_5__* pm_dev; struct vnode* pm_devvp; int /*<<< orphan*/  pm_cp; scalar_t__ pm_u2d; scalar_t__ pm_d2u; scalar_t__ pm_u2w; scalar_t__ pm_w2u; } ;
struct mount {int /*<<< orphan*/  mnt_flag; int /*<<< orphan*/ * mnt_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  si_mountpt; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* close ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int ENXIO ; 
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_LOCAL ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int MSDOSFSMNT_KICONV ; 
 int MSDOSFSMNT_RONLY ; 
 int /*<<< orphan*/  M_MSDOSFSFAT ; 
 int /*<<< orphan*/  M_MSDOSFSMNT ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_NEXT (struct vnode*,int /*<<< orphan*/ ) ; 
 struct msdosfsmount* VFSTOMSDOSFS (struct mount*) ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dev_rel (TYPE_5__*) ; 
 int /*<<< orphan*/  free (struct msdosfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_vfs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdestroy (int /*<<< orphan*/ *) ; 
 int markvoldirty (struct msdosfsmount*,int) ; 
 TYPE_4__* msdosfs_iconv ; 
 int msdosfs_sync (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 int /*<<< orphan*/  v_actfreelist ; 
 int vflush (struct mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_printf (struct vnode*,char*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
msdosfs_unmount(struct mount *mp, int mntflags)
{
	struct msdosfsmount *pmp;
	int error, flags;

	error = flags = 0;
	pmp = VFSTOMSDOSFS(mp);
	if ((pmp->pm_flags & MSDOSFSMNT_RONLY) == 0)
		error = msdosfs_sync(mp, MNT_WAIT);
	if ((mntflags & MNT_FORCE) != 0)
		flags |= FORCECLOSE;
	else if (error != 0)
		return (error);
	error = vflush(mp, 0, flags, curthread);
	if (error != 0 && error != ENXIO)
		return (error);
	if ((pmp->pm_flags & MSDOSFSMNT_RONLY) == 0) {
		error = markvoldirty(pmp, 0);
		if (error && error != ENXIO) {
			(void)markvoldirty(pmp, 1);
			return (error);
		}
	}
	if (pmp->pm_flags & MSDOSFSMNT_KICONV && msdosfs_iconv) {
		if (pmp->pm_w2u)
			msdosfs_iconv->close(pmp->pm_w2u);
		if (pmp->pm_u2w)
			msdosfs_iconv->close(pmp->pm_u2w);
		if (pmp->pm_d2u)
			msdosfs_iconv->close(pmp->pm_d2u);
		if (pmp->pm_u2d)
			msdosfs_iconv->close(pmp->pm_u2d);
	}

#ifdef MSDOSFS_DEBUG
	{
		struct vnode *vp = pmp->pm_devvp;
		struct bufobj *bo;

		bo = &vp->v_bufobj;
		BO_LOCK(bo);
		VI_LOCK(vp);
		vn_printf(vp,
		    "msdosfs_umount(): just before calling VOP_CLOSE()\n");
		printf("freef %p, freeb %p, mount %p\n",
		    TAILQ_NEXT(vp, v_actfreelist), vp->v_actfreelist.tqe_prev,
		    vp->v_mount);
		printf("cleanblkhd %p, dirtyblkhd %p, numoutput %ld, type %d\n",
		    TAILQ_FIRST(&vp->v_bufobj.bo_clean.bv_hd),
		    TAILQ_FIRST(&vp->v_bufobj.bo_dirty.bv_hd),
		    vp->v_bufobj.bo_numoutput, vp->v_type);
		VI_UNLOCK(vp);
		BO_UNLOCK(bo);
	}
#endif
	g_topology_lock();
	g_vfs_close(pmp->pm_cp);
	g_topology_unlock();
	atomic_store_rel_ptr((uintptr_t *)&pmp->pm_dev->si_mountpt, 0);
	vrele(pmp->pm_devvp);
	dev_rel(pmp->pm_dev);
	free(pmp->pm_inusemap, M_MSDOSFSFAT);
	lockdestroy(&pmp->pm_fatlock);
	free(pmp, M_MSDOSFSMNT);
	mp->mnt_data = NULL;
	MNT_ILOCK(mp);
	mp->mnt_flag &= ~MNT_LOCAL;
	MNT_IUNLOCK(mp);
	return (error);
}
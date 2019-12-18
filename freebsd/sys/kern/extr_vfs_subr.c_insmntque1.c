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
struct vnode {int v_vflag; int v_iflag; struct mount* v_mount; } ;
struct mount {int mnt_kern_flag; scalar_t__ mnt_nvnodelistsize; int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_activevnodelistsize; int /*<<< orphan*/  mnt_activevnodelist; int /*<<< orphan*/  mnt_nvnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MNTK_UNMOUNT ; 
 int MNTK_UNMOUNTF ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REF (struct mount*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_ACTIVE ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VNASSERT (int,struct vnode*,char*) ; 
 int VV_FORCEINSMQ ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_actfreelist ; 
 int /*<<< orphan*/  v_nmntvnodes ; 

int
insmntque1(struct vnode *vp, struct mount *mp,
	void (*dtr)(struct vnode *, void *), void *dtr_arg)
{

	KASSERT(vp->v_mount == NULL,
		("insmntque: vnode already on per mount vnode list"));
	VNASSERT(mp != NULL, vp, ("Don't call insmntque(foo, NULL)"));
	ASSERT_VOP_ELOCKED(vp, "insmntque: non-locked vp");

	/*
	 * We acquire the vnode interlock early to ensure that the
	 * vnode cannot be recycled by another process releasing a
	 * holdcnt on it before we get it on both the vnode list
	 * and the active vnode list. The mount mutex protects only
	 * manipulation of the vnode list and the vnode freelist
	 * mutex protects only manipulation of the active vnode list.
	 * Hence the need to hold the vnode interlock throughout.
	 */
	MNT_ILOCK(mp);
	VI_LOCK(vp);
	if (((mp->mnt_kern_flag & MNTK_UNMOUNT) != 0 &&
	    ((mp->mnt_kern_flag & MNTK_UNMOUNTF) != 0 ||
	    mp->mnt_nvnodelistsize == 0)) &&
	    (vp->v_vflag & VV_FORCEINSMQ) == 0) {
		VI_UNLOCK(vp);
		MNT_IUNLOCK(mp);
		if (dtr != NULL)
			dtr(vp, dtr_arg);
		return (EBUSY);
	}
	vp->v_mount = mp;
	MNT_REF(mp);
	TAILQ_INSERT_TAIL(&mp->mnt_nvnodelist, vp, v_nmntvnodes);
	VNASSERT(mp->mnt_nvnodelistsize >= 0, vp,
		("neg mount point vnode list size"));
	mp->mnt_nvnodelistsize++;
	KASSERT((vp->v_iflag & VI_ACTIVE) == 0,
	    ("Activating already active vnode"));
	vp->v_iflag |= VI_ACTIVE;
	mtx_lock(&mp->mnt_listmtx);
	TAILQ_INSERT_HEAD(&mp->mnt_activevnodelist, vp, v_actfreelist);
	mp->mnt_activevnodelistsize++;
	mtx_unlock(&mp->mnt_listmtx);
	VI_UNLOCK(vp);
	MNT_IUNLOCK(mp);
	return (0);
}
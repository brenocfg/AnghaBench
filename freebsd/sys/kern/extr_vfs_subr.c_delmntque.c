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
struct vnode {int v_iflag; struct mount* v_mount; } ;
struct mount {scalar_t__ mnt_activevnodelistsize; scalar_t__ mnt_nvnodelistsize; int /*<<< orphan*/  mnt_nvnodelist; int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_activevnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_ACTIVE ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VNASSERT (int,struct vnode*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_actfreelist ; 
 int /*<<< orphan*/  v_nmntvnodes ; 

__attribute__((used)) static void
delmntque(struct vnode *vp)
{
	struct mount *mp;
	int active;

	mp = vp->v_mount;
	if (mp == NULL)
		return;
	MNT_ILOCK(mp);
	VI_LOCK(vp);
	KASSERT(mp->mnt_activevnodelistsize <= mp->mnt_nvnodelistsize,
	    ("Active vnode list size %d > Vnode list size %d",
	     mp->mnt_activevnodelistsize, mp->mnt_nvnodelistsize));
	active = vp->v_iflag & VI_ACTIVE;
	vp->v_iflag &= ~VI_ACTIVE;
	if (active) {
		mtx_lock(&mp->mnt_listmtx);
		TAILQ_REMOVE(&mp->mnt_activevnodelist, vp, v_actfreelist);
		mp->mnt_activevnodelistsize--;
		mtx_unlock(&mp->mnt_listmtx);
	}
	vp->v_mount = NULL;
	VI_UNLOCK(vp);
	VNASSERT(mp->mnt_nvnodelistsize > 0, vp,
		("bad mount point vnode list size"));
	TAILQ_REMOVE(&mp->mnt_nvnodelist, vp, v_nmntvnodes);
	mp->mnt_nvnodelistsize--;
	MNT_REL(mp);
	MNT_IUNLOCK(mp);
}
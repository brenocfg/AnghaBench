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
struct bufobj {int dummy; } ;
struct vnode {struct bufobj v_bufobj; int /*<<< orphan*/  v_vflag; int /*<<< orphan*/  v_type; } ;
struct mount {struct vnode* mnt_syncer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  VNON ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VV_FORCEINSMQ ; 
 int getnewvnode (char*,struct mount*,int /*<<< orphan*/ *,struct vnode**) ; 
 int insmntque (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  sync_vnode_count ; 
 int /*<<< orphan*/  sync_vnodeops ; 
 long syncdelay ; 
 long syncer_maxdelay ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vn_syncer_add_to_worklist (struct bufobj*,long) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

void
vfs_allocate_syncvnode(struct mount *mp)
{
	struct vnode *vp;
	struct bufobj *bo;
	static long start, incr, next;
	int error;

	/* Allocate a new vnode */
	error = getnewvnode("syncer", mp, &sync_vnodeops, &vp);
	if (error != 0)
		panic("vfs_allocate_syncvnode: getnewvnode() failed");
	vp->v_type = VNON;
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	vp->v_vflag |= VV_FORCEINSMQ;
	error = insmntque(vp, mp);
	if (error != 0)
		panic("vfs_allocate_syncvnode: insmntque() failed");
	vp->v_vflag &= ~VV_FORCEINSMQ;
	VOP_UNLOCK(vp, 0);
	/*
	 * Place the vnode onto the syncer worklist. We attempt to
	 * scatter them about on the list so that they will go off
	 * at evenly distributed times even if all the filesystems
	 * are mounted at once.
	 */
	next += incr;
	if (next == 0 || next > syncer_maxdelay) {
		start /= 2;
		incr /= 2;
		if (start == 0) {
			start = syncer_maxdelay / 2;
			incr = syncer_maxdelay;
		}
		next = start;
	}
	bo = &vp->v_bufobj;
	BO_LOCK(bo);
	vn_syncer_add_to_worklist(bo, syncdelay > 0 ? next % syncdelay : 0);
	/* XXX - vn_syncer_add_to_worklist() also grabs and drops sync_mtx. */
	mtx_lock(&sync_mtx);
	sync_vnode_count++;
	if (mp->mnt_syncer == NULL) {
		mp->mnt_syncer = vp;
		vp = NULL;
	}
	mtx_unlock(&sync_mtx);
	BO_UNLOCK(bo);
	if (vp != NULL) {
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		vgone(vp);
		vput(vp);
	}
}
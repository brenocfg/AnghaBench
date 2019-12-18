#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct bufobj {int bo_flag; } ;
struct vnode {TYPE_1__* v_mount; struct bufobj v_bufobj; } ;
struct TYPE_2__ {struct vnode* mnt_syncer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int BO_ONWORKLST ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_synclist ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  sync_vnode_count ; 
 int /*<<< orphan*/  syncer_worklist_len ; 

__attribute__((used)) static int
sync_reclaim(struct vop_reclaim_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct bufobj *bo;

	bo = &vp->v_bufobj;
	BO_LOCK(bo);
	mtx_lock(&sync_mtx);
	if (vp->v_mount->mnt_syncer == vp)
		vp->v_mount->mnt_syncer = NULL;
	if (bo->bo_flag & BO_ONWORKLST) {
		LIST_REMOVE(bo, bo_synclist);
		syncer_worklist_len--;
		sync_vnode_count--;
		bo->bo_flag &= ~BO_ONWORKLST;
	}
	mtx_unlock(&sync_mtx);
	BO_UNLOCK(bo);

	return (0);
}
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
struct vnode {struct mount* v_mount; int /*<<< orphan*/  v_type; } ;
struct mount {int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_activevnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REF (struct mount*) ; 
 int /*<<< orphan*/  M_VNODE_MARKER ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct vnode* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct vnode*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMARKER ; 
 struct vnode* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnt_vnode_markerfree_active (struct vnode**,struct mount*) ; 
 struct vnode* mnt_vnode_next_active (struct vnode**,struct mount*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_actfreelist ; 

struct vnode *
__mnt_vnode_first_active(struct vnode **mvp, struct mount *mp)
{
	struct vnode *vp;

	*mvp = malloc(sizeof(struct vnode), M_VNODE_MARKER, M_WAITOK | M_ZERO);
	MNT_ILOCK(mp);
	MNT_REF(mp);
	MNT_IUNLOCK(mp);
	(*mvp)->v_type = VMARKER;
	(*mvp)->v_mount = mp;

	mtx_lock(&mp->mnt_listmtx);
	vp = TAILQ_FIRST(&mp->mnt_activevnodelist);
	if (vp == NULL) {
		mtx_unlock(&mp->mnt_listmtx);
		mnt_vnode_markerfree_active(mvp, mp);
		return (NULL);
	}
	TAILQ_INSERT_BEFORE(vp, *mvp, v_actfreelist);
	return (mnt_vnode_next_active(mvp, mp));
}
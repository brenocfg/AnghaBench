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
struct vnode {struct mount* v_mount; } ;
struct mount {int /*<<< orphan*/  mnt_nvnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int /*<<< orphan*/  M_VNODE_MARKER ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_nmntvnodes ; 

void
__mnt_vnode_markerfree_all(struct vnode **mvp, struct mount *mp)
{

	if (*mvp == NULL) {
		MNT_IUNLOCK(mp);
		return;
	}

	mtx_assert(MNT_MTX(mp), MA_OWNED);

	KASSERT((*mvp)->v_mount == mp, ("marker vnode mount list mismatch"));
	TAILQ_REMOVE(&mp->mnt_nvnodelist, *mvp, v_nmntvnodes);
	MNT_REL(mp);
	MNT_IUNLOCK(mp);
	free(*mvp, M_VNODE_MARKER);
	*mvp = NULL;
}
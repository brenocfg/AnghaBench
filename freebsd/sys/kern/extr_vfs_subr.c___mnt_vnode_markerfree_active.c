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
struct vnode {int dummy; } ;
struct mount {int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_activevnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_vnode_markerfree_active (struct vnode**,struct mount*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_actfreelist ; 

void
__mnt_vnode_markerfree_active(struct vnode **mvp, struct mount *mp)
{

	if (*mvp == NULL)
		return;

	mtx_lock(&mp->mnt_listmtx);
	TAILQ_REMOVE(&mp->mnt_activevnodelist, *mvp, v_actfreelist);
	mtx_unlock(&mp->mnt_listmtx);
	mnt_vnode_markerfree_active(mvp, mp);
}
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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  null_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLV_NOUNLOCK ; 
 TYPE_1__* VTONULL (struct vnode*) ; 
 struct vnode* null_hashget (struct mount*,struct vnode*) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static void
nullfs_reclaim_lowervp(struct mount *mp, struct vnode *lowervp)
{
	struct vnode *vp;

	vp = null_hashget(mp, lowervp);
	if (vp == NULL)
		return;
	VTONULL(vp)->null_flags |= NULLV_NOUNLOCK;
	vgone(vp);
	vput(vp);
}
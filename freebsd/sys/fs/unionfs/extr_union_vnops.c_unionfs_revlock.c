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

/* Variables and functions */
 int LK_EXCLUSIVE ; 
 int LK_RELEASE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int) ; 
 scalar_t__ vn_lock (struct vnode*,int) ; 

__attribute__((used)) static void
unionfs_revlock(struct vnode *vp, int flags)
{
	if (flags & LK_RELEASE)
		VOP_UNLOCK(vp, flags);
	else {
		/* UPGRADE */
		if (vn_lock(vp, flags) != 0)
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	}
}
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
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  VOP_LOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 

__attribute__((used)) static void
pfs_purge_one(struct vnode *vnp)
{

	VOP_LOCK(vnp, LK_EXCLUSIVE);
	vgone(vnp);
	VOP_UNLOCK(vnp, 0);
	vdrop(vnp);
}
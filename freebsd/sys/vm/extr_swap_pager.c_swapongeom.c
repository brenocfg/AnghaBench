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
struct vnode {scalar_t__ v_type; int v_iflag; int /*<<< orphan*/  v_rdev; } ;

/* Variables and functions */
 int ENOENT ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 scalar_t__ VCHR ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int swapongeom_locked (int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
swapongeom(struct vnode *vp)
{
	int error;

	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	if (vp->v_type != VCHR || (vp->v_iflag & VI_DOOMED) != 0) {
		error = ENOENT;
	} else {
		g_topology_lock();
		error = swapongeom_locked(vp->v_rdev, vp);
		g_topology_unlock();
	}
	VOP_UNLOCK(vp, 0);
	return (error);
}
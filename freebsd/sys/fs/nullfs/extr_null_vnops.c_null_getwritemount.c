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
struct vop_getwritemount_args {int /*<<< orphan*/ ** a_mpp; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct null_node {struct vnode* null_lowervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VOP_GETWRITEMOUNT (struct vnode*,int /*<<< orphan*/ **) ; 
 struct null_node* VTONULL (struct vnode*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vholdnz (struct vnode*) ; 

__attribute__((used)) static int
null_getwritemount(struct vop_getwritemount_args *ap)
{
	struct null_node *xp;
	struct vnode *lowervp;
	struct vnode *vp;

	vp = ap->a_vp;
	VI_LOCK(vp);
	xp = VTONULL(vp);
	if (xp && (lowervp = xp->null_lowervp)) {
		vholdnz(lowervp);
		VI_UNLOCK(vp);
		VOP_GETWRITEMOUNT(lowervp, ap->a_mpp);
		vdrop(lowervp);
	} else {
		VI_UNLOCK(vp);
		*(ap->a_mpp) = NULL;
	}
	return (0);
}
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
struct vop_remove_args {struct componentname* a_cnp; struct vnode* a_vp; struct vnode* a_dvp; } ;
struct vnode {int dummy; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  FUSE_UNLINK ; 
 int fuse_internal_remove (struct vnode*,struct vnode*,struct componentname*,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 scalar_t__ vnode_isdir (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_remove(struct vop_remove_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct vnode *vp = ap->a_vp;
	struct componentname *cnp = ap->a_cnp;

	int err;

	if (fuse_isdeadfs(vp)) {
		return ENXIO;
	}
	if (vnode_isdir(vp)) {
		return EPERM;
	}

	err = fuse_internal_remove(dvp, vp, cnp, FUSE_UNLINK);

	return err;
}
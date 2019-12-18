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
struct vop_fsync_args {struct vnode* a_vp; } ;
struct vnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_check_mtime (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_update (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_fsync(struct vop_fsync_args *v)
{
	struct vnode *vp = v->a_vp;

	MPASS(VOP_ISLOCKED(vp));

	tmpfs_check_mtime(vp);
	tmpfs_update(vp);

	return 0;
}
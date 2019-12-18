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
struct vop_close_args {int /*<<< orphan*/  a_fflag; struct thread* a_td; struct ucred* a_cred; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_object; } ;
struct unionfs_node_status {scalar_t__ uns_lower_opencnt; scalar_t__ uns_upper_opencnt; int uns_node_flag; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_DOWNGRADE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_UPGRADE ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int UNS_OPENL_4_READDIR ; 
 int VOP_CLOSE (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  unionfs_get_node_status (struct unionfs_node*,struct thread*,struct unionfs_node_status**) ; 
 int /*<<< orphan*/  unionfs_tryrem_node_status (struct unionfs_node*,struct unionfs_node_status*) ; 
 scalar_t__ vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
unionfs_close(struct vop_close_args *ap)
{
	int		error;
	int		locked;
	struct unionfs_node *unp;
	struct unionfs_node_status *unsp;
	struct ucred   *cred;
	struct thread  *td;
	struct vnode   *vp;
	struct vnode   *ovp;

	UNIONFS_INTERNAL_DEBUG("unionfs_close: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	locked = 0;
	vp = ap->a_vp;
	unp = VTOUNIONFS(vp);
	cred = ap->a_cred;
	td = ap->a_td;

	if (VOP_ISLOCKED(vp) != LK_EXCLUSIVE) {
		if (vn_lock(vp, LK_UPGRADE) != 0)
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		locked = 1;
	}
	unionfs_get_node_status(unp, td, &unsp);

	if (unsp->uns_lower_opencnt <= 0 && unsp->uns_upper_opencnt <= 0) {
#ifdef DIAGNOSTIC
		printf("unionfs_close: warning: open count is 0\n");
#endif
		if (unp->un_uppervp != NULLVP)
			ovp = unp->un_uppervp;
		else
			ovp = unp->un_lowervp;
	} else if (unsp->uns_upper_opencnt > 0)
		ovp = unp->un_uppervp;
	else
		ovp = unp->un_lowervp;

	error = VOP_CLOSE(ovp, ap->a_fflag, cred, td);

	if (error != 0)
		goto unionfs_close_abort;

	vp->v_object = ovp->v_object;

	if (ovp == unp->un_uppervp) {
		unsp->uns_upper_opencnt--;
		if (unsp->uns_upper_opencnt == 0) {
			if (unsp->uns_node_flag & UNS_OPENL_4_READDIR) {
				VOP_CLOSE(unp->un_lowervp, FREAD, cred, td);
				unsp->uns_node_flag &= ~UNS_OPENL_4_READDIR;
				unsp->uns_lower_opencnt--;
			}
			if (unsp->uns_lower_opencnt > 0)
				vp->v_object = unp->un_lowervp->v_object;
		}
	} else
		unsp->uns_lower_opencnt--;

unionfs_close_abort:
	unionfs_tryrem_node_status(unp, unsp);

	if (locked != 0)
		vn_lock(vp, LK_DOWNGRADE | LK_RETRY);

	UNIONFS_INTERNAL_DEBUG("unionfs_close: leave (%d)\n", error);

	return (error);
}
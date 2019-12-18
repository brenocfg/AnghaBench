#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_open_args {int a_mode; TYPE_1__* a_vp; int /*<<< orphan*/ * a_fp; struct thread* a_td; struct ucred* a_cred; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_object; } ;
struct unionfs_node_status {scalar_t__ uns_lower_opencnt; scalar_t__ uns_upper_opencnt; int uns_lower_openmode; int /*<<< orphan*/  uns_node_flag; } ;
struct unionfs_node {struct vnode* un_uppervp; struct vnode* un_lowervp; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_object; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (TYPE_1__*) ; 
 struct vnode* NULLVP ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int /*<<< orphan*/  UNS_OPENL_4_READDIR ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VOP_CLOSE (struct vnode*,int,struct ucred*,struct thread*) ; 
 int VOP_OPEN (struct vnode*,int,struct ucred*,struct thread*,int /*<<< orphan*/ *) ; 
 scalar_t__ VREG ; 
 struct unionfs_node* VTOUNIONFS (TYPE_1__*) ; 
 int unionfs_copyfile (struct unionfs_node*,int,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/  unionfs_get_node_status (struct unionfs_node*,struct thread*,struct unionfs_node_status**) ; 
 int /*<<< orphan*/  unionfs_tryrem_node_status (struct unionfs_node*,struct unionfs_node_status*) ; 

__attribute__((used)) static int
unionfs_open(struct vop_open_args *ap)
{
	int		error;
	struct unionfs_node *unp;
	struct unionfs_node_status *unsp;
	struct vnode   *uvp;
	struct vnode   *lvp;
	struct vnode   *targetvp;
	struct ucred   *cred;
	struct thread  *td;

	UNIONFS_INTERNAL_DEBUG("unionfs_open: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	error = 0;
	unp = VTOUNIONFS(ap->a_vp);
	uvp = unp->un_uppervp;
	lvp = unp->un_lowervp;
	targetvp = NULLVP;
	cred = ap->a_cred;
	td = ap->a_td;

	unionfs_get_node_status(unp, td, &unsp);

	if (unsp->uns_lower_opencnt > 0 || unsp->uns_upper_opencnt > 0) {
		/* vnode is already opend. */
		if (unsp->uns_upper_opencnt > 0)
			targetvp = uvp;
		else
			targetvp = lvp;

		if (targetvp == lvp &&
		    (ap->a_mode & FWRITE) && lvp->v_type == VREG)
			targetvp = NULLVP;
	}
	if (targetvp == NULLVP) {
		if (uvp == NULLVP) {
			if ((ap->a_mode & FWRITE) && lvp->v_type == VREG) {
				error = unionfs_copyfile(unp,
				    !(ap->a_mode & O_TRUNC), cred, td);
				if (error != 0)
					goto unionfs_open_abort;
				targetvp = uvp = unp->un_uppervp;
			} else
				targetvp = lvp;
		} else
			targetvp = uvp;
	}

	error = VOP_OPEN(targetvp, ap->a_mode, cred, td, ap->a_fp);
	if (error == 0) {
		if (targetvp == uvp) {
			if (uvp->v_type == VDIR && lvp != NULLVP &&
			    unsp->uns_lower_opencnt <= 0) {
				/* open lower for readdir */
				error = VOP_OPEN(lvp, FREAD, cred, td, NULL);
				if (error != 0) {
					VOP_CLOSE(uvp, ap->a_mode, cred, td);
					goto unionfs_open_abort;
				}
				unsp->uns_node_flag |= UNS_OPENL_4_READDIR;
				unsp->uns_lower_opencnt++;
			}
			unsp->uns_upper_opencnt++;
		} else {
			unsp->uns_lower_opencnt++;
			unsp->uns_lower_openmode = ap->a_mode;
		}
		ap->a_vp->v_object = targetvp->v_object;
	}

unionfs_open_abort:
	if (error != 0)
		unionfs_tryrem_node_status(unp, unsp);

	UNIONFS_INTERNAL_DEBUG("unionfs_open: leave (%d)\n", error);

	return (error);
}
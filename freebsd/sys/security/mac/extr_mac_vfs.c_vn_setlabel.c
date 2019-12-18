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
struct vnode {scalar_t__ v_type; TYPE_1__* v_mount; } ;
struct ucred {int dummy; } ;
struct label {int dummy; } ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EBADF ; 
 int EOPNOTSUPP ; 
 int MNT_MULTILABEL ; 
 int /*<<< orphan*/  VADMIN ; 
 scalar_t__ VNON ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ) ; 
 int VOP_SETLABEL (struct vnode*,struct label*,struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int mac_vnode_check_relabel (struct ucred*,struct vnode*,struct label*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
vn_setlabel(struct vnode *vp, struct label *intlabel, struct ucred *cred)
{
	int error;

	if (vp->v_mount == NULL) {
		/* printf("vn_setlabel: null v_mount\n"); */
		if (vp->v_type != VNON)
			printf("vn_setlabel: null v_mount with non-VNON\n");
		return (EBADF);
	}

	if ((vp->v_mount->mnt_flag & MNT_MULTILABEL) == 0)
		return (EOPNOTSUPP);

	/*
	 * Multi-phase commit.  First check the policies to confirm the
	 * change is OK.  Then commit via the filesystem.  Finally, update
	 * the actual vnode label.
	 *
	 * Question: maybe the filesystem should update the vnode at the end
	 * as part of VOP_SETLABEL()?
	 */
	error = mac_vnode_check_relabel(cred, vp, intlabel);
	if (error)
		return (error);

	/*
	 * VADMIN provides the opportunity for the filesystem to make
	 * decisions about who is and is not able to modify labels and
	 * protections on files.  This might not be right.  We can't assume
	 * VOP_SETLABEL() will do it, because we might implement that as part
	 * of vop_stdsetlabel_ea().
	 */
	error = VOP_ACCESS(vp, VADMIN, cred, curthread);
	if (error)
		return (error);

	error = VOP_SETLABEL(vp, intlabel, cred, curthread);
	if (error)
		return (error);

	return (0);
}
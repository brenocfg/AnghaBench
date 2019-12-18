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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int i_mode; } ;

/* Variables and functions */
 int EPERM ; 
 int ISVTX ; 
 int /*<<< orphan*/  VADMIN ; 
 int VDELETE ; 
 int VDELETE_CHILD ; 
 int /*<<< orphan*/  VEXEC ; 
 int VEXPLICIT_DENY ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int VOP_ACCESSX (struct vnode*,int,struct ucred*,struct thread*) ; 
 TYPE_1__* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  VWRITE ; 

__attribute__((used)) static int
ufs_delete_denied(struct vnode *vdp, struct vnode *tdp, struct ucred *cred,
    struct thread *td)
{
	int error;

#ifdef UFS_ACL
	/*
	 * NFSv4 Minor Version 1, draft-ietf-nfsv4-minorversion1-03.txt
	 *
	 * 3.16.2.1. ACE4_DELETE vs. ACE4_DELETE_CHILD
	 */

	/*
	 * XXX: Is this check required?
	 */
	error = VOP_ACCESS(vdp, VEXEC, cred, td);
	if (error)
		return (error);

	error = VOP_ACCESSX(tdp, VDELETE, cred, td);
	if (error == 0)
		return (0);

	error = VOP_ACCESSX(vdp, VDELETE_CHILD, cred, td);
	if (error == 0)
		return (0);

	error = VOP_ACCESSX(vdp, VEXPLICIT_DENY | VDELETE_CHILD, cred, td);
	if (error)
		return (error);

#endif /* !UFS_ACL */

	/*
	 * Standard Unix access control - delete access requires VWRITE.
	 */
	error = VOP_ACCESS(vdp, VWRITE, cred, td);
	if (error)
		return (error);

	/*
	 * If directory is "sticky", then user must own
	 * the directory, or the file in it, else she
	 * may not delete it (unless she's root). This
	 * implements append-only directories.
	 */
	if ((VTOI(vdp)->i_mode & ISVTX) &&
	    VOP_ACCESS(vdp, VADMIN, cred, td) &&
	    VOP_ACCESS(tdp, VADMIN, cred, td))
		return (EPERM);

	return (0);
}
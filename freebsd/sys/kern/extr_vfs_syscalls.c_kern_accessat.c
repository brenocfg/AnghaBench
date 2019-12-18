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
struct ucred {scalar_t__ cr_uid; scalar_t__ cr_ruid; scalar_t__ cr_rgid; scalar_t__* cr_groups; } ;
struct thread {struct ucred* td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AT_BENEATH ; 
 int AT_EACCESS ; 
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int) ; 
 int BENEATH ; 
 int EINVAL ; 
 int FOLLOW ; 
 int F_OK ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 int /*<<< orphan*/  cap_fstat_rights ; 
 struct ucred* crdup (struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int namei (struct nameidata*) ; 
 int vn_access (struct vnode*,int,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
kern_accessat(struct thread *td, int fd, const char *path,
    enum uio_seg pathseg, int flag, int amode)
{
	struct ucred *cred, *usecred;
	struct vnode *vp;
	struct nameidata nd;
	int error;

	if ((flag & ~(AT_EACCESS | AT_BENEATH)) != 0)
		return (EINVAL);
	if (amode != F_OK && (amode & ~(R_OK | W_OK | X_OK)) != 0)
		return (EINVAL);

	/*
	 * Create and modify a temporary credential instead of one that
	 * is potentially shared (if we need one).
	 */
	cred = td->td_ucred;
	if ((flag & AT_EACCESS) == 0 &&
	    ((cred->cr_uid != cred->cr_ruid ||
	    cred->cr_rgid != cred->cr_groups[0]))) {
		usecred = crdup(cred);
		usecred->cr_uid = cred->cr_ruid;
		usecred->cr_groups[0] = cred->cr_rgid;
		td->td_ucred = usecred;
	} else
		usecred = cred;
	AUDIT_ARG_VALUE(amode);
	NDINIT_ATRIGHTS(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF |
	    AUDITVNODE1 | ((flag & AT_BENEATH) != 0 ? BENEATH : 0),
	    pathseg, path, fd, &cap_fstat_rights, td);
	if ((error = namei(&nd)) != 0)
		goto out;
	vp = nd.ni_vp;

	error = vn_access(vp, amode, usecred, td);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vput(vp);
out:
	if (usecred != cred) {
		td->td_ucred = cred;
		crfree(usecred);
	}
	return (error);
}
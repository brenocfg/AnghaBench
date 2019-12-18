#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct vattr {int va_mode; int /*<<< orphan*/  va_type; } ;
struct thread {int /*<<< orphan*/  td_ucred; TYPE_2__* td_proc; } ;
struct TYPE_7__ {int /*<<< orphan*/  cn_flags; } ;
struct nameidata {struct vnode* ni_vp; struct vnode* ni_dvp; TYPE_3__ ni_cnd; } ;
struct mount {int dummy; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_6__ {TYPE_1__* p_fd; } ;
struct TYPE_5__ {int fd_cmask; } ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_MODE (int) ; 
 int /*<<< orphan*/  CREATE ; 
 int EEXIST ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int NOCACHE ; 
 int PCATCH ; 
 int SAVENAME ; 
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 int /*<<< orphan*/  VDIR ; 
 int VOP_MKDIR (struct vnode*,struct vnode**,TYPE_3__*,struct vattr*) ; 
 int V_NOWAIT ; 
 int V_XSLEEP ; 
 int /*<<< orphan*/  WILLBEDIR ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int /*<<< orphan*/  cap_mkdirat_rights ; 
 int mac_vnode_check_create (int /*<<< orphan*/ ,struct vnode*,TYPE_3__*,struct vattr*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
kern_mkdirat(struct thread *td, int fd, const char *path, enum uio_seg segflg,
    int mode)
{
	struct mount *mp;
	struct vnode *vp;
	struct vattr vattr;
	struct nameidata nd;
	int error;

	AUDIT_ARG_MODE(mode);
restart:
	bwillwrite();
	NDINIT_ATRIGHTS(&nd, CREATE, LOCKPARENT | SAVENAME | AUDITVNODE1 |
	    NOCACHE, segflg, path, fd, &cap_mkdirat_rights,
	    td);
	nd.ni_cnd.cn_flags |= WILLBEDIR;
	if ((error = namei(&nd)) != 0)
		return (error);
	vp = nd.ni_vp;
	if (vp != NULL) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		/*
		 * XXX namei called with LOCKPARENT but not LOCKLEAF has
		 * the strange behaviour of leaving the vnode unlocked
		 * if the target is the same vnode as the parent.
		 */
		if (vp == nd.ni_dvp)
			vrele(nd.ni_dvp);
		else
			vput(nd.ni_dvp);
		vrele(vp);
		return (EEXIST);
	}
	if (vn_start_write(nd.ni_dvp, &mp, V_NOWAIT) != 0) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		vput(nd.ni_dvp);
		if ((error = vn_start_write(NULL, &mp, V_XSLEEP | PCATCH)) != 0)
			return (error);
		goto restart;
	}
	VATTR_NULL(&vattr);
	vattr.va_type = VDIR;
	vattr.va_mode = (mode & ACCESSPERMS) &~ td->td_proc->p_fd->fd_cmask;
#ifdef MAC
	error = mac_vnode_check_create(td->td_ucred, nd.ni_dvp, &nd.ni_cnd,
	    &vattr);
	if (error != 0)
		goto out;
#endif
	error = VOP_MKDIR(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr);
#ifdef MAC
out:
#endif
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vput(nd.ni_dvp);
	if (error == 0)
		vput(nd.ni_vp);
	vn_finished_write(mp);
	return (error);
}
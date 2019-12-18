#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vattr {int va_mode; int /*<<< orphan*/  va_type; } ;
struct thread {int /*<<< orphan*/  td_ucred; TYPE_2__* td_proc; } ;
struct nameidata {scalar_t__ ni_vp; scalar_t__ ni_dvp; int /*<<< orphan*/  ni_cnd; } ;
struct mount {int dummy; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_4__ {TYPE_1__* p_fd; } ;
struct TYPE_3__ {int fd_cmask; } ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_TEXT (char const*) ; 
 int /*<<< orphan*/  CREATE ; 
 int EEXIST ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int NOCACHE ; 
 int PCATCH ; 
 int SAVENAME ; 
 int UIO_SYSSPACE ; 
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 int /*<<< orphan*/  VLNK ; 
 int VOP_SYMLINK (scalar_t__,scalar_t__*,int /*<<< orphan*/ *,struct vattr*,char const*) ; 
 int V_NOWAIT ; 
 int V_XSLEEP ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int /*<<< orphan*/  cap_symlinkat_rights ; 
 int copyinstr (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mac_vnode_check_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct vattr*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  namei_zone ; 
 char* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_start_write (int /*<<< orphan*/ *,struct mount**,int) ; 
 int /*<<< orphan*/  vput (scalar_t__) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 

int
kern_symlinkat(struct thread *td, const char *path1, int fd, const char *path2,
    enum uio_seg segflg)
{
	struct mount *mp;
	struct vattr vattr;
	const char *syspath;
	char *tmppath;
	struct nameidata nd;
	int error;

	if (segflg == UIO_SYSSPACE) {
		syspath = path1;
	} else {
		tmppath = uma_zalloc(namei_zone, M_WAITOK);
		if ((error = copyinstr(path1, tmppath, MAXPATHLEN, NULL)) != 0)
			goto out;
		syspath = tmppath;
	}
	AUDIT_ARG_TEXT(syspath);
restart:
	bwillwrite();
	NDINIT_ATRIGHTS(&nd, CREATE, LOCKPARENT | SAVENAME | AUDITVNODE1 |
	    NOCACHE, segflg, path2, fd, &cap_symlinkat_rights,
	    td);
	if ((error = namei(&nd)) != 0)
		goto out;
	if (nd.ni_vp) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		if (nd.ni_vp == nd.ni_dvp)
			vrele(nd.ni_dvp);
		else
			vput(nd.ni_dvp);
		vrele(nd.ni_vp);
		error = EEXIST;
		goto out;
	}
	if (vn_start_write(nd.ni_dvp, &mp, V_NOWAIT) != 0) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		vput(nd.ni_dvp);
		if ((error = vn_start_write(NULL, &mp, V_XSLEEP | PCATCH)) != 0)
			goto out;
		goto restart;
	}
	VATTR_NULL(&vattr);
	vattr.va_mode = ACCESSPERMS &~ td->td_proc->p_fd->fd_cmask;
#ifdef MAC
	vattr.va_type = VLNK;
	error = mac_vnode_check_create(td->td_ucred, nd.ni_dvp, &nd.ni_cnd,
	    &vattr);
	if (error != 0)
		goto out2;
#endif
	error = VOP_SYMLINK(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr, syspath);
	if (error == 0)
		vput(nd.ni_vp);
#ifdef MAC
out2:
#endif
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vput(nd.ni_dvp);
	vn_finished_write(mp);
out:
	if (segflg != UIO_SYSSPACE)
		uma_zfree(namei_zone, tmppath);
	return (error);
}
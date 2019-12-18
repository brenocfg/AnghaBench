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
struct vnode {scalar_t__ v_type; int v_vflag; int v_iflag; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_dvp; int /*<<< orphan*/  ni_cnd; struct vnode* ni_vp; } ;
struct mount {int dummy; } ;
struct file {struct vnode* f_vnode; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int AT_BENEATH ; 
 int AUDITVNODE1 ; 
 int BENEATH ; 
 int /*<<< orphan*/  CAP_LOOKUP ; 
 int /*<<< orphan*/  DELETE ; 
 int EBADF ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EINVAL ; 
 int ENOTDIR ; 
 int FD_NONE ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int PCATCH ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VFS_NOTIFY_UPPER_UNLINK ; 
 int VI_DOOMED ; 
 int VOP_RMDIR (struct vnode*,struct vnode*,int /*<<< orphan*/ *) ; 
 int VV_ROOT ; 
 int V_NOWAIT ; 
 int V_XSLEEP ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_unlinkat_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int,int /*<<< orphan*/ ,struct file**) ; 
 int mac_vnode_check_unlink (int /*<<< orphan*/ ,struct vnode*,struct vnode*,int /*<<< orphan*/ *) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vfs_notify_upper (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
kern_frmdirat(struct thread *td, int dfd, const char *path, int fd,
    enum uio_seg pathseg, int flag)
{
	struct mount *mp;
	struct vnode *vp;
	struct file *fp;
	struct nameidata nd;
	cap_rights_t rights;
	int error;

	fp = NULL;
	if (fd != FD_NONE) {
		error = getvnode(td, fd, cap_rights_init(&rights, CAP_LOOKUP),
		    &fp);
		if (error != 0)
			return (error);
	}

restart:
	bwillwrite();
	NDINIT_ATRIGHTS(&nd, DELETE, LOCKPARENT | LOCKLEAF | AUDITVNODE1 |
	    ((flag & AT_BENEATH) != 0 ? BENEATH : 0),
	    pathseg, path, dfd, &cap_unlinkat_rights, td);
	if ((error = namei(&nd)) != 0)
		goto fdout;
	vp = nd.ni_vp;
	if (vp->v_type != VDIR) {
		error = ENOTDIR;
		goto out;
	}
	/*
	 * No rmdir "." please.
	 */
	if (nd.ni_dvp == vp) {
		error = EINVAL;
		goto out;
	}
	/*
	 * The root of a mounted filesystem cannot be deleted.
	 */
	if (vp->v_vflag & VV_ROOT) {
		error = EBUSY;
		goto out;
	}

	if (fp != NULL && fp->f_vnode != vp) {
		if ((fp->f_vnode->v_iflag & VI_DOOMED) != 0)
			error = EBADF;
		else
			error = EDEADLK;
		goto out;
	}

#ifdef MAC
	error = mac_vnode_check_unlink(td->td_ucred, nd.ni_dvp, vp,
	    &nd.ni_cnd);
	if (error != 0)
		goto out;
#endif
	if (vn_start_write(nd.ni_dvp, &mp, V_NOWAIT) != 0) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		vput(vp);
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
		else
			vput(nd.ni_dvp);
		if ((error = vn_start_write(NULL, &mp, V_XSLEEP | PCATCH)) != 0)
			goto fdout;
		goto restart;
	}
	vfs_notify_upper(vp, VFS_NOTIFY_UPPER_UNLINK);
	error = VOP_RMDIR(nd.ni_dvp, nd.ni_vp, &nd.ni_cnd);
	vn_finished_write(mp);
out:
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vput(vp);
	if (nd.ni_dvp == vp)
		vrele(nd.ni_dvp);
	else
		vput(nd.ni_dvp);
fdout:
	if (fp != NULL)
		fdrop(fp, td);
	return (error);
}
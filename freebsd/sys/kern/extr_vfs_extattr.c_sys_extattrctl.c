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
struct vnode {struct mount* v_mount; } ;
struct thread {int dummy; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct mount {int dummy; } ;
struct extattrctl_args {int /*<<< orphan*/ * attrname; int /*<<< orphan*/  attrnamespace; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * path; int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int AUDITVNODE2 ; 
 int /*<<< orphan*/  AUDIT_ARG_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_TEXT (char*) ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int /*<<< orphan*/ ) ; 
 int EXTATTR_MAXNAMELEN ; 
 int FOLLOW ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_NO_VP_RELE ; 
 int /*<<< orphan*/  NDF_NO_VP_UNLOCK ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*) ; 
 int PCATCH ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int VFS_EXTATTRCTL (struct mount*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int V_WAIT ; 
 int copyinstr (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int namei (struct nameidata*) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
sys_extattrctl(struct thread *td, struct extattrctl_args *uap)
{
	struct vnode *filename_vp;
	struct nameidata nd;
	struct mount *mp, *mp_writable;
	char attrname[EXTATTR_MAXNAMELEN];
	int error;

	AUDIT_ARG_CMD(uap->cmd);
	AUDIT_ARG_VALUE(uap->attrnamespace);
	/*
	 * uap->attrname is not always defined.  We check again later when we
	 * invoke the VFS call so as to pass in NULL there if needed.
	 */
	if (uap->attrname != NULL) {
		error = copyinstr(uap->attrname, attrname, EXTATTR_MAXNAMELEN,
		    NULL);
		if (error)
			return (error);
	}
	AUDIT_ARG_TEXT(attrname);

	mp = NULL;
	filename_vp = NULL;
	if (uap->filename != NULL) {
		NDINIT(&nd, LOOKUP, FOLLOW | AUDITVNODE2,
		    UIO_USERSPACE, uap->filename, td);
		error = namei(&nd);
		if (error)
			return (error);
		filename_vp = nd.ni_vp;
		NDFREE(&nd, NDF_NO_VP_RELE);
	}

	/* uap->path is always defined. */
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF | AUDITVNODE1,
	    UIO_USERSPACE, uap->path, td);
	error = namei(&nd);
	if (error)
		goto out;
	mp = nd.ni_vp->v_mount;
	error = vfs_busy(mp, 0);
	if (error) {
		NDFREE(&nd, 0);
		mp = NULL;
		goto out;
	}
	VOP_UNLOCK(nd.ni_vp, 0);
	error = vn_start_write(nd.ni_vp, &mp_writable, V_WAIT | PCATCH);
	NDFREE(&nd, NDF_NO_VP_UNLOCK);
	if (error)
		goto out;
	if (filename_vp != NULL) {
		/*
		 * uap->filename is not always defined.  If it is,
		 * grab a vnode lock, which VFS_EXTATTRCTL() will
		 * later release.
		 */
		error = vn_lock(filename_vp, LK_EXCLUSIVE);
		if (error) {
			vn_finished_write(mp_writable);
			goto out;
		}
	}

	error = VFS_EXTATTRCTL(mp, uap->cmd, filename_vp, uap->attrnamespace,
	    uap->attrname != NULL ? attrname : NULL);

	vn_finished_write(mp_writable);
out:
	if (mp != NULL)
		vfs_unbusy(mp);

	/*
	 * VFS_EXTATTRCTL will have unlocked, but not de-ref'd, filename_vp,
	 * so vrele it if it is defined.
	 */
	if (filename_vp != NULL)
		vrele(filename_vp);
	return (error);
}
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
struct thread {int td_dupfd; int* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct mount {int dummy; } ;
struct file {int f_seqcount; int f_flag; struct vnode* f_vnode; int /*<<< orphan*/ * f_ops; } ;
struct fhopen_args {int /*<<< orphan*/  u_fhp; int /*<<< orphan*/  flags; } ;
struct fhandle {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;
typedef  int /*<<< orphan*/  fhp ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_VNODE ; 
 int EINVAL ; 
 int ESTALE ; 
 int FFLAGS (int /*<<< orphan*/ ) ; 
 int FHASLOCK ; 
 int FMASK ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  PRIV_VFS_FHOPEN ; 
 int VFS_FHTOVP (struct mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  badfileops ; 
 int copyin (int /*<<< orphan*/ ,struct fhandle*,int) ; 
 int falloc_noinstall (struct thread*,struct file**) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ *) ; 
 int finstall (struct thread*,struct file*,int*,int,int /*<<< orphan*/ *) ; 
 int fo_truncate (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 struct mount* vfs_busyfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int vn_open_vnode (struct vnode*,int,int /*<<< orphan*/ ,struct thread*,struct file*) ; 
 int /*<<< orphan*/  vnops ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
sys_fhopen(struct thread *td, struct fhopen_args *uap)
{
	struct mount *mp;
	struct vnode *vp;
	struct fhandle fhp;
	struct file *fp;
	int fmode, error;
	int indx;

	error = priv_check(td, PRIV_VFS_FHOPEN);
	if (error != 0)
		return (error);
	indx = -1;
	fmode = FFLAGS(uap->flags);
	/* why not allow a non-read/write open for our lockd? */
	if (((fmode & (FREAD | FWRITE)) == 0) || (fmode & O_CREAT))
		return (EINVAL);
	error = copyin(uap->u_fhp, &fhp, sizeof(fhp));
	if (error != 0)
		return(error);
	/* find the mount point */
	mp = vfs_busyfs(&fhp.fh_fsid);
	if (mp == NULL)
		return (ESTALE);
	/* now give me my vnode, it gets returned to me locked */
	error = VFS_FHTOVP(mp, &fhp.fh_fid, LK_EXCLUSIVE, &vp);
	vfs_unbusy(mp);
	if (error != 0)
		return (error);

	error = falloc_noinstall(td, &fp);
	if (error != 0) {
		vput(vp);
		return (error);
	}
	/*
	 * An extra reference on `fp' has been held for us by
	 * falloc_noinstall().
	 */

#ifdef INVARIANTS
	td->td_dupfd = -1;
#endif
	error = vn_open_vnode(vp, fmode, td->td_ucred, td, fp);
	if (error != 0) {
		KASSERT(fp->f_ops == &badfileops,
		    ("VOP_OPEN in fhopen() set f_ops"));
		KASSERT(td->td_dupfd < 0,
		    ("fhopen() encountered fdopen()"));

		vput(vp);
		goto bad;
	}
#ifdef INVARIANTS
	td->td_dupfd = 0;
#endif
	fp->f_vnode = vp;
	fp->f_seqcount = 1;
	finit(fp, (fmode & FMASK) | (fp->f_flag & FHASLOCK), DTYPE_VNODE, vp,
	    &vnops);
	VOP_UNLOCK(vp, 0);
	if ((fmode & O_TRUNC) != 0) {
		error = fo_truncate(fp, 0, td->td_ucred, td);
		if (error != 0)
			goto bad;
	}

	error = finstall(td, fp, &indx, fmode, NULL);
bad:
	fdrop(fp, td);
	td->td_retval[0] = indx;
	return (error);
}
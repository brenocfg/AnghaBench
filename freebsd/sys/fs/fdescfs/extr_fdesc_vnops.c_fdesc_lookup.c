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
typedef  int u_int ;
struct vop_lookup_args {struct componentname* a_cnp; struct vnode* a_dvp; struct vnode** a_vpp; } ;
struct vnode {int v_iflag; } ;
struct thread {int dummy; } ;
struct file {int dummy; } ;
struct fdesc_get_ino_args {int fd_fd; struct thread* td; struct file* fp; scalar_t__ ix; int /*<<< orphan*/  ftype; } ;
struct componentname {char* cn_nameptr; int cn_namelen; int cn_flags; scalar_t__ cn_nameiop; struct thread* cn_thread; } ;
struct TYPE_2__ {scalar_t__ fd_type; scalar_t__ fd_ix; } ;

/* Variables and functions */
 scalar_t__ DELETE ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int EROFS ; 
 scalar_t__ FD_DESC ; 
 int /*<<< orphan*/  Fdesc ; 
 scalar_t__ Froot ; 
 int ISLASTCN ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 scalar_t__ RENAME ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 TYPE_1__* VTOFDESC (struct vnode*) ; 
 int /*<<< orphan*/  cap_no_rights ; 
 int /*<<< orphan*/  fdesc_get_ino_alloc ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_vget_ino_gen (struct vnode*,int /*<<< orphan*/ ,struct fdesc_get_ino_args*,int,struct vnode**) ; 

__attribute__((used)) static int
fdesc_lookup(struct vop_lookup_args *ap)
{
	struct vnode **vpp = ap->a_vpp;
	struct vnode *dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	char *pname = cnp->cn_nameptr;
	struct thread *td = cnp->cn_thread;
	struct file *fp;
	struct fdesc_get_ino_args arg;
	int nlen = cnp->cn_namelen;
	u_int fd, fd1;
	int error;
	struct vnode *fvp;

	if ((cnp->cn_flags & ISLASTCN) &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)) {
		error = EROFS;
		goto bad;
	}

	if (cnp->cn_namelen == 1 && *pname == '.') {
		*vpp = dvp;
		VREF(dvp);
		return (0);
	}

	if (VTOFDESC(dvp)->fd_type != Froot) {
		error = ENOTDIR;
		goto bad;
	}

	fd = 0;
	/* the only time a leading 0 is acceptable is if it's "0" */
	if (*pname == '0' && nlen != 1) {
		error = ENOENT;
		goto bad;
	}
	while (nlen--) {
		if (*pname < '0' || *pname > '9') {
			error = ENOENT;
			goto bad;
		}
		fd1 = 10 * fd + *pname++ - '0';
		if (fd1 < fd) {
			error = ENOENT;
			goto bad;
		}
		fd = fd1;
	}

	/*
	 * No rights to check since 'fp' isn't actually used.
	 */
	if ((error = fget(td, fd, &cap_no_rights, &fp)) != 0)
		goto bad;

	/* Check if we're looking up ourselves. */
	if (VTOFDESC(dvp)->fd_ix == FD_DESC + fd) {
		/*
		 * In case we're holding the last reference to the file, the dvp
		 * will be re-acquired.
		 */
		vhold(dvp);
		VOP_UNLOCK(dvp, 0);
		fdrop(fp, td);

		/* Re-aquire the lock afterwards. */
		vn_lock(dvp, LK_RETRY | LK_EXCLUSIVE);
		vdrop(dvp);
		fvp = dvp;
		if ((dvp->v_iflag & VI_DOOMED) != 0)
			error = ENOENT;
	} else {
		/*
		 * Unlock our root node (dvp) when doing this, since we might
		 * deadlock since the vnode might be locked by another thread
		 * and the root vnode lock will be obtained afterwards (in case
		 * we're looking up the fd of the root vnode), which will be the
		 * opposite lock order. Vhold the root vnode first so we don't
		 * lose it.
		 */
		arg.ftype = Fdesc;
		arg.fd_fd = fd;
		arg.ix = FD_DESC + fd;
		arg.fp = fp;
		arg.td = td;
		error = vn_vget_ino_gen(dvp, fdesc_get_ino_alloc, &arg,
		    LK_EXCLUSIVE, &fvp);
	}

	if (error)
		goto bad;
	*vpp = fvp;
	return (0);

bad:
	*vpp = NULL;
	return (error);
}
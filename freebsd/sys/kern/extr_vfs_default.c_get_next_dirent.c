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
struct vnode {scalar_t__ v_type; } ;
struct uio {int uio_iovcnt; int uio_resid; int /*<<< orphan*/  uio_offset; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct iovec {char* iov_base; int iov_len; } ;
struct dirent {int d_reclen; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int DIRENT_MINSIZE ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ VDIR ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int VOP_READDIR (struct vnode*,struct uio*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mac_vnode_check_readdir (int /*<<< orphan*/ ,struct vnode*) ; 

__attribute__((used)) static int
get_next_dirent(struct vnode *vp, struct dirent **dpp, char *dirbuf,
		int dirbuflen, off_t *off, char **cpos, int *len,
		int *eofflag, struct thread *td)
{
	int error, reclen;
	struct uio uio;
	struct iovec iov;
	struct dirent *dp;

	KASSERT(VOP_ISLOCKED(vp), ("vp %p is not locked", vp));
	KASSERT(vp->v_type == VDIR, ("vp %p is not a directory", vp));

	if (*len == 0) {
		iov.iov_base = dirbuf;
		iov.iov_len = dirbuflen;

		uio.uio_iov = &iov;
		uio.uio_iovcnt = 1;
		uio.uio_offset = *off;
		uio.uio_resid = dirbuflen;
		uio.uio_segflg = UIO_SYSSPACE;
		uio.uio_rw = UIO_READ;
		uio.uio_td = td;

		*eofflag = 0;

#ifdef MAC
		error = mac_vnode_check_readdir(td->td_ucred, vp);
		if (error == 0)
#endif
			error = VOP_READDIR(vp, &uio, td->td_ucred, eofflag,
		    		NULL, NULL);
		if (error)
			return (error);

		*off = uio.uio_offset;

		*cpos = dirbuf;
		*len = (dirbuflen - uio.uio_resid);

		if (*len == 0)
			return (ENOENT);
	}

	dp = (struct dirent *)(*cpos);
	reclen = dp->d_reclen;
	*dpp = dp;

	/* check for malformed directory.. */
	if (reclen < DIRENT_MINSIZE)
		return (EINVAL);

	*cpos += reclen;
	*len -= reclen;

	return (0);
}
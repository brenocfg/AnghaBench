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
struct vnode {TYPE_1__* v_mount; } ;
struct uio {int uio_iovcnt; scalar_t__ uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct ufs2_dinode {scalar_t__ di_extsize; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;
struct inode {int i_ea_error; scalar_t__ i_ea_len; scalar_t__ i_ea_refs; int /*<<< orphan*/ * i_ea_area; struct ufs2_dinode* i_din2; } ;
struct TYPE_2__ {struct ucred* mnt_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EINVAL ; 
 int IO_EXT ; 
 int IO_SYNC ; 
 int /*<<< orphan*/  M_TEMP ; 
 struct ucred* NOCRED ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 struct inode* VTOI (struct vnode*) ; 
 int ffs_extwrite (struct vnode*,struct uio*,int,struct ucred*) ; 
 int /*<<< orphan*/  ffs_lock_ea (struct vnode*) ; 
 int ffs_truncate (struct vnode*,int /*<<< orphan*/ ,int,struct ucred*) ; 
 int /*<<< orphan*/  ffs_unlock_ea (struct vnode*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_close_ea(struct vnode *vp, int commit, struct ucred *cred, struct thread *td)
{
	struct inode *ip;
	struct uio luio;
	struct iovec liovec;
	int error;
	struct ufs2_dinode *dp;

	ip = VTOI(vp);

	ffs_lock_ea(vp);
	if (ip->i_ea_area == NULL) {
		ffs_unlock_ea(vp);
		return (EINVAL);
	}
	dp = ip->i_din2;
	error = ip->i_ea_error;
	if (commit && error == 0) {
		ASSERT_VOP_ELOCKED(vp, "ffs_close_ea commit");
		if (cred == NOCRED)
			cred =  vp->v_mount->mnt_cred;
		liovec.iov_base = ip->i_ea_area;
		liovec.iov_len = ip->i_ea_len;
		luio.uio_iov = &liovec;
		luio.uio_iovcnt = 1;
		luio.uio_offset = 0;
		luio.uio_resid = ip->i_ea_len;
		luio.uio_segflg = UIO_SYSSPACE;
		luio.uio_rw = UIO_WRITE;
		luio.uio_td = td;
		/* XXX: I'm not happy about truncating to zero size */
		if (ip->i_ea_len < dp->di_extsize)
			error = ffs_truncate(vp, 0, IO_EXT, cred);
		error = ffs_extwrite(vp, &luio, IO_EXT | IO_SYNC, cred);
	}
	if (--ip->i_ea_refs == 0) {
		free(ip->i_ea_area, M_TEMP);
		ip->i_ea_area = NULL;
		ip->i_ea_len = 0;
		ip->i_ea_error = 0;
	}
	ffs_unlock_ea(vp);
	return (error);
}
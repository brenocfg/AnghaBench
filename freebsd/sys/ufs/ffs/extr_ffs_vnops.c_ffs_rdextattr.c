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
typedef  int uoff_t ;
typedef  void* u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; void* uio_resid; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct ufs2_dinode {void* di_extsize; } ;
struct thread {int dummy; } ;
struct iovec {void* iov_len; int /*<<< orphan*/ * iov_base; } ;
struct inode {struct ufs2_dinode* i_din2; } ;
struct fs {int fs_bsize; } ;

/* Variables and functions */
 int EFBIG ; 
 int IO_EXT ; 
 int IO_SYNC ; 
 struct fs* ITOFS (struct inode*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int UFS_NXADDR ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 struct inode* VTOI (struct vnode*) ; 
 int ffs_extread (struct vnode*,struct uio*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_rdextattr(u_char **p, struct vnode *vp, struct thread *td, int extra)
{
	struct inode *ip;
	struct ufs2_dinode *dp;
	struct fs *fs;
	struct uio luio;
	struct iovec liovec;
	u_int easize;
	int error;
	u_char *eae;

	ip = VTOI(vp);
	fs = ITOFS(ip);
	dp = ip->i_din2;
	easize = dp->di_extsize;
	if ((uoff_t)easize + extra > UFS_NXADDR * fs->fs_bsize)
		return (EFBIG);

	eae = malloc(easize + extra, M_TEMP, M_WAITOK);

	liovec.iov_base = eae;
	liovec.iov_len = easize;
	luio.uio_iov = &liovec;
	luio.uio_iovcnt = 1;
	luio.uio_offset = 0;
	luio.uio_resid = easize;
	luio.uio_segflg = UIO_SYSSPACE;
	luio.uio_rw = UIO_READ;
	luio.uio_td = td;

	error = ffs_extread(vp, &luio, IO_EXT | IO_SYNC);
	if (error) {
		free(eae, M_TEMP);
		return(error);
	}
	*p = eae;
	return (0);
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; int uio_resid; TYPE_1__* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct iovec {int iov_len; struct dirent* iov_base; } ;
struct dirent {scalar_t__ d_type; int d_namlen; char* d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_UNKNOWN ; 
 scalar_t__ DT_WHT ; 
 int ENOTEMPTY ; 
 int GENERIC_DIRSIZ (struct dirent*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READDIR (struct vnode*,struct uio*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  free (struct dirent*,int /*<<< orphan*/ ) ; 
 struct dirent* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vfs_emptydir(struct vnode *vp)
{
	struct uio uio;
	struct iovec iov;
	struct dirent *dirent, *dp, *endp;
	int error, eof;

	error = 0;
	eof = 0;

	ASSERT_VOP_LOCKED(vp, "vfs_emptydir");

	dirent = malloc(sizeof(struct dirent), M_TEMP, M_WAITOK);
	iov.iov_base = dirent;
	iov.iov_len = sizeof(struct dirent);

	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = 0;
	uio.uio_resid = sizeof(struct dirent);
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_rw = UIO_READ;
	uio.uio_td = curthread;

	while (eof == 0 && error == 0) {
		error = VOP_READDIR(vp, &uio, curthread->td_ucred, &eof,
		    NULL, NULL);
		if (error != 0)
			break;
		endp = (void *)((uint8_t *)dirent +
		    sizeof(struct dirent) - uio.uio_resid);
		for (dp = dirent; dp < endp;
		     dp = (void *)((uint8_t *)dp + GENERIC_DIRSIZ(dp))) {
			if (dp->d_type == DT_WHT)
				continue;
			if (dp->d_namlen == 0)
				continue;
			if (dp->d_type != DT_DIR &&
			    dp->d_type != DT_UNKNOWN) {
				error = ENOTEMPTY;
				break;
			}
			if (dp->d_namlen > 2) {
				error = ENOTEMPTY;
				break;
			}
			if (dp->d_namlen == 1 &&
			    dp->d_name[0] != '.') {
				error = ENOTEMPTY;
				break;
			}
			if (dp->d_namlen == 2 &&
			    dp->d_name[1] != '.') {
				error = ENOTEMPTY;
				break;
			}
			uio.uio_resid = sizeof(struct dirent);
		}
	}
	free(dirent, M_TEMP);
	return (error);
}
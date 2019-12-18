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
typedef  int /*<<< orphan*/  uio ;
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; int uio_resid; void* uio_offset; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; int /*<<< orphan*/  uio_segflg; struct thread* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  void* off_t ;

/* Variables and functions */
 void* MAXBSIZE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int VOP_READ (struct vnode*,struct uio*,int /*<<< orphan*/ ,struct ucred*) ; 
 int VOP_WRITE (struct vnode*,struct uio*,int /*<<< orphan*/ ,struct ucred*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
unionfs_copyfile_core(struct vnode *lvp, struct vnode *uvp,
		      struct ucred *cred, struct thread *td)
{
	int		error;
	off_t		offset;
	int		count;
	int		bufoffset;
	char           *buf;
	struct uio	uio;
	struct iovec	iov;

	error = 0;
	memset(&uio, 0, sizeof(uio));

	uio.uio_td = td;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_offset = 0;

	buf = malloc(MAXBSIZE, M_TEMP, M_WAITOK);

	while (error == 0) {
		offset = uio.uio_offset;

		uio.uio_iov = &iov;
		uio.uio_iovcnt = 1;
		iov.iov_base = buf;
		iov.iov_len = MAXBSIZE;
		uio.uio_resid = iov.iov_len;
		uio.uio_rw = UIO_READ;

		if ((error = VOP_READ(lvp, &uio, 0, cred)) != 0)
			break;
		if ((count = MAXBSIZE - uio.uio_resid) == 0)
			break;

		bufoffset = 0;
		while (bufoffset < count) {
			uio.uio_iov = &iov;
			uio.uio_iovcnt = 1;
			iov.iov_base = buf + bufoffset;
			iov.iov_len = count - bufoffset;
			uio.uio_offset = offset + bufoffset;
			uio.uio_resid = iov.iov_len;
			uio.uio_rw = UIO_WRITE;

			if ((error = VOP_WRITE(uvp, &uio, 0, cred)) != 0)
				break;

			bufoffset += (count - bufoffset) - uio.uio_resid;
		}

		uio.uio_offset = offset + bufoffset;
	}

	free(buf, M_TEMP);

	return (error);
}
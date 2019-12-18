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
struct uio {int uio_iovcnt; int uio_resid; scalar_t__ uio_offset; struct thread* uio_td; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct iovec {int iov_len; char* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int IO_NODELOCKED ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_GETEXTATTR (struct vnode*,int,char const*,struct uio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

int
vn_extattr_get(struct vnode *vp, int ioflg, int attrnamespace,
    const char *attrname, int *buflen, char *buf, struct thread *td)
{
	struct uio	auio;
	struct iovec	iov;
	int	error;

	iov.iov_len = *buflen;
	iov.iov_base = buf;

	auio.uio_iov = &iov;
	auio.uio_iovcnt = 1;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_td = td;
	auio.uio_offset = 0;
	auio.uio_resid = *buflen;

	if ((ioflg & IO_NODELOCKED) == 0)
		vn_lock(vp, LK_SHARED | LK_RETRY);

	ASSERT_VOP_LOCKED(vp, "IO_NODELOCKED with no vp lock held");

	/* authorize attribute retrieval as kernel */
	error = VOP_GETEXTATTR(vp, attrnamespace, attrname, &auio, NULL, NULL,
	    td);

	if ((ioflg & IO_NODELOCKED) == 0)
		VOP_UNLOCK(vp, 0);

	if (error == 0) {
		*buflen = *buflen - auio.uio_resid;
	}

	return (error);
}
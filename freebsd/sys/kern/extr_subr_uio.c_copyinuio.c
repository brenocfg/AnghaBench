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
typedef  int u_int ;
struct uio {int uio_iovcnt; int uio_offset; scalar_t__ uio_resid; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct iovec {scalar_t__ iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IOSIZE_MAX ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyin (struct iovec const*,struct iovec*,int) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 struct uio* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
copyinuio(const struct iovec *iovp, u_int iovcnt, struct uio **uiop)
{
	struct iovec *iov;
	struct uio *uio;
	u_int iovlen;
	int error, i;

	*uiop = NULL;
	if (iovcnt > UIO_MAXIOV)
		return (EINVAL);
	iovlen = iovcnt * sizeof (struct iovec);
	uio = malloc(iovlen + sizeof *uio, M_IOV, M_WAITOK);
	iov = (struct iovec *)(uio + 1);
	error = copyin(iovp, iov, iovlen);
	if (error) {
		free(uio, M_IOV);
		return (error);
	}
	uio->uio_iov = iov;
	uio->uio_iovcnt = iovcnt;
	uio->uio_segflg = UIO_USERSPACE;
	uio->uio_offset = -1;
	uio->uio_resid = 0;
	for (i = 0; i < iovcnt; i++) {
		if (iov->iov_len > IOSIZE_MAX - uio->uio_resid) {
			free(uio, M_IOV);
			return (EINVAL);
		}
		uio->uio_resid += iov->iov_len;
		iov++;
	}
	*uiop = uio;
	return (0);
}
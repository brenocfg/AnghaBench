#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uio {size_t uio_iovcnt; int uio_offset; scalar_t__ uio_resid; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  iovobj ;
struct TYPE_5__ {scalar_t__ buf_len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ cloudabi64_iovec_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TO_PTR (int /*<<< orphan*/ ) ; 
 size_t UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyin (TYPE_1__ const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 struct uio* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cloudabi64_copyinuio(const cloudabi64_iovec_t *iovp, size_t iovcnt,
    struct uio **uiop)
{
	cloudabi64_iovec_t iovobj;
	struct uio *uio;
	struct iovec *iov;
	size_t i;
	int error;

	/* Allocate uio and iovecs. */
	if (iovcnt > UIO_MAXIOV)
		return (EINVAL);
	uio = malloc(sizeof(struct uio) + iovcnt * sizeof(struct iovec),
	    M_IOV, M_WAITOK);
	iov = (struct iovec *)(uio + 1);

	/* Initialize uio. */
	uio->uio_iov = iov;
	uio->uio_iovcnt = iovcnt;
	uio->uio_segflg = UIO_USERSPACE;
	uio->uio_offset = -1;
	uio->uio_resid = 0;

	/* Copy in iovecs. */
	for (i = 0; i < iovcnt; i++) {
		error = copyin(&iovp[i], &iovobj, sizeof(iovobj));
		if (error != 0) {
			free(uio, M_IOV);
			return (error);
		}
		iov[i].iov_base = TO_PTR(iovobj.buf);
		iov[i].iov_len = iovobj.buf_len;
		if (iov[i].iov_len > INT64_MAX - uio->uio_resid) {
			free(uio, M_IOV);
			return (EINVAL);
		}
		uio->uio_resid += iov[i].iov_len;
	}

	*uiop = uio;
	return (0);
}
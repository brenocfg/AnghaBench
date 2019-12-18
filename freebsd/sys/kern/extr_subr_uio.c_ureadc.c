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
struct uio {scalar_t__ uio_iovcnt; scalar_t__ uio_resid; int uio_segflg; int /*<<< orphan*/  uio_offset; struct iovec* uio_iov; } ;
struct iovec {scalar_t__ iov_len; char* iov_base; } ;

/* Variables and functions */
 int EFAULT ; 
#define  UIO_NOCOPY 130 
#define  UIO_SYSSPACE 129 
#define  UIO_USERSPACE 128 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  subyte (char*,int) ; 

int
ureadc(int c, struct uio *uio)
{
	struct iovec *iov;
	char *iov_base;

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "Calling ureadc()");

again:
	if (uio->uio_iovcnt == 0 || uio->uio_resid == 0)
		panic("ureadc");
	iov = uio->uio_iov;
	if (iov->iov_len == 0) {
		uio->uio_iovcnt--;
		uio->uio_iov++;
		goto again;
	}
	switch (uio->uio_segflg) {

	case UIO_USERSPACE:
		if (subyte(iov->iov_base, c) < 0)
			return (EFAULT);
		break;

	case UIO_SYSSPACE:
		iov_base = iov->iov_base;
		*iov_base = c;
		break;

	case UIO_NOCOPY:
		break;
	}
	iov->iov_base = (char *)iov->iov_base + 1;
	iov->iov_len--;
	uio->uio_resid--;
	uio->uio_offset++;
	return (0);
}
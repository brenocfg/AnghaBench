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
struct uio {scalar_t__ uio_segflg; scalar_t__ uio_resid; int uio_iovcnt; struct iovec* uio_iov; } ;
struct iovec {char* iov_base; size_t iov_len; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t PAGE_SIZE ; 
 scalar_t__ UIO_USERSPACE ; 
 int vn_io_fault_touch (char*,struct uio const*) ; 

__attribute__((used)) static int
vn_io_fault_prefault_user(const struct uio *uio)
{
	char *base;
	const struct iovec *iov;
	size_t len;
	ssize_t resid;
	int error, i;

	KASSERT(uio->uio_segflg == UIO_USERSPACE,
	    ("vn_io_fault_prefault userspace"));

	error = i = 0;
	iov = uio->uio_iov;
	resid = uio->uio_resid;
	base = iov->iov_base;
	len = iov->iov_len;
	while (resid > 0) {
		error = vn_io_fault_touch(base, uio);
		if (error != 0)
			break;
		if (len < PAGE_SIZE) {
			if (len != 0) {
				error = vn_io_fault_touch(base + len - 1, uio);
				if (error != 0)
					break;
				resid -= len;
			}
			if (++i >= uio->uio_iovcnt)
				break;
			iov = uio->uio_iov + i;
			base = iov->iov_base;
			len = iov->iov_len;
		} else {
			len -= PAGE_SIZE;
			base += PAGE_SIZE;
			resid -= PAGE_SIZE;
		}
	}
	return (error);
}
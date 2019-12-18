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
struct uio {int uio_iovcnt; size_t uio_resid; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t IOSIZE_MAX ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_pwritev (struct thread*,int,struct uio*,int /*<<< orphan*/ ) ; 

int
kern_pwrite(struct thread *td, int fd, const void *buf, size_t nbyte,
    off_t offset)
{
	struct uio auio;
	struct iovec aiov;
	int error;

	if (nbyte > IOSIZE_MAX)
		return (EINVAL);
	aiov.iov_base = (void *)(uintptr_t)buf;
	aiov.iov_len = nbyte;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_resid = nbyte;
	auio.uio_segflg = UIO_USERSPACE;
	error = kern_pwritev(td, fd, &auio, offset);
	return (error);
}
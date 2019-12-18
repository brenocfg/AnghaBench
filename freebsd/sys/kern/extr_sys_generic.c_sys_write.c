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
struct write_args {scalar_t__ nbyte; int /*<<< orphan*/  fd; scalar_t__ buf; } ;
struct uio {int uio_iovcnt; scalar_t__ uio_resid; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct iovec {scalar_t__ iov_len; void* iov_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IOSIZE_MAX ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_writev (struct thread*,int /*<<< orphan*/ ,struct uio*) ; 

int
sys_write(struct thread *td, struct write_args *uap)
{
	struct uio auio;
	struct iovec aiov;
	int error;

	if (uap->nbyte > IOSIZE_MAX)
		return (EINVAL);
	aiov.iov_base = (void *)(uintptr_t)uap->buf;
	aiov.iov_len = uap->nbyte;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_resid = uap->nbyte;
	auio.uio_segflg = UIO_USERSPACE;
	error = kern_writev(td, uap->fd, &auio);
	return (error);
}
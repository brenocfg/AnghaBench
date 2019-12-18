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
struct uio {int uio_iovcnt; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_resid; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct cloudabi_sys_random_get_args {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int read_random_uio (struct uio*,int) ; 

int
cloudabi_sys_random_get(struct thread *td,
    struct cloudabi_sys_random_get_args *uap)
{
	struct iovec iov = {
		.iov_base = uap->buf,
		.iov_len = uap->buf_len
	};
	struct uio uio = {
		.uio_iov = &iov,
		.uio_iovcnt = 1,
		.uio_resid = iov.iov_len,
		.uio_segflg = UIO_USERSPACE,
		.uio_rw = UIO_READ,
		.uio_td = td
	};

	return (read_random_uio(&uio, false));
}
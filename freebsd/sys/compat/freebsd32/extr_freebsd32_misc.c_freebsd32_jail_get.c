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
struct uio {int /*<<< orphan*/ * uio_iov; } ;
struct thread {int dummy; } ;
struct iovec32 {int dummy; } ;
struct freebsd32_jail_get_args {int iovcnt; scalar_t__ iovp; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  iov32 ;

/* Variables and functions */
 int /*<<< orphan*/  CP (int /*<<< orphan*/ ,struct iovec32,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  PTROUT_CP (int /*<<< orphan*/ ,struct iovec32,int /*<<< orphan*/ ) ; 
 int copyout (struct iovec32*,scalar_t__,int) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int freebsd32_copyinuio (scalar_t__,int,struct uio**) ; 
 int /*<<< orphan*/  iov_base ; 
 int /*<<< orphan*/  iov_len ; 
 int kern_jail_get (struct thread*,struct uio*,int /*<<< orphan*/ ) ; 

int
freebsd32_jail_get(struct thread *td, struct freebsd32_jail_get_args *uap)
{
	struct iovec32 iov32;
	struct uio *auio;
	int error, i;

	/* Check that we have an even number of iovecs. */
	if (uap->iovcnt & 1)
		return (EINVAL);

	error = freebsd32_copyinuio(uap->iovp, uap->iovcnt, &auio);
	if (error)
		return (error);
	error = kern_jail_get(td, auio, uap->flags);
	if (error == 0)
		for (i = 0; i < uap->iovcnt; i++) {
			PTROUT_CP(auio->uio_iov[i], iov32, iov_base);
			CP(auio->uio_iov[i], iov32, iov_len);
			error = copyout(&iov32, uap->iovp + i, sizeof(iov32));
			if (error != 0)
				break;
		}
	free(auio, M_IOV);
	return (error);
}
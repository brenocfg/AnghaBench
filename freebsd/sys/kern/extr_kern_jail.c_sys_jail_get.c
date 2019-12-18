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
struct uio {int /*<<< orphan*/  uio_iov; } ;
struct thread {int dummy; } ;
struct jail_get_args {int iovcnt; int /*<<< orphan*/  iovp; int /*<<< orphan*/  flags; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_IOV ; 
 int copyinuio (int /*<<< orphan*/ ,int,struct uio**) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int kern_jail_get (struct thread*,struct uio*,int /*<<< orphan*/ ) ; 

int
sys_jail_get(struct thread *td, struct jail_get_args *uap)
{
	struct uio *auio;
	int error;

	/* Check that we have an even number of iovecs. */
	if (uap->iovcnt & 1)
		return (EINVAL);

	error = copyinuio(uap->iovp, uap->iovcnt, &auio);
	if (error)
		return (error);
	error = kern_jail_get(td, auio, uap->flags);
	if (error == 0)
		error = copyout(auio->uio_iov, uap->iovp,
		    uap->iovcnt * sizeof (struct iovec));
	free(auio, M_IOV);
	return (error);
}
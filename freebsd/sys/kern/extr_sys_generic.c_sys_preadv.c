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
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct preadv_args {int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; int /*<<< orphan*/  iovcnt; int /*<<< orphan*/  iovp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IOV ; 
 int copyinuio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio**) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int kern_preadv (struct thread*,int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ) ; 

int
sys_preadv(struct thread *td, struct preadv_args *uap)
{
	struct uio *auio;
	int error;

	error = copyinuio(uap->iovp, uap->iovcnt, &auio);
	if (error)
		return (error);
	error = kern_preadv(td, uap->fd, auio, uap->offset);
	free(auio, M_IOV);
	return (error);
}
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
struct writev_args {int /*<<< orphan*/  fd; int /*<<< orphan*/  iovcnt; int /*<<< orphan*/  iovp; } ;
struct uio {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IOV ; 
 int copyinuio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio**) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int kern_writev (struct thread*,int /*<<< orphan*/ ,struct uio*) ; 

int
sys_writev(struct thread *td, struct writev_args *uap)
{
	struct uio *auio;
	int error;

	error = copyinuio(uap->iovp, uap->iovcnt, &auio);
	if (error)
		return (error);
	error = kern_writev(td, uap->fd, auio);
	free(auio, M_IOV);
	return (error);
}
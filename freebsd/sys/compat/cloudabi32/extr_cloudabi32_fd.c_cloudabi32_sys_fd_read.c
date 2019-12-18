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
struct cloudabi32_sys_fd_read_args {int /*<<< orphan*/  fd; int /*<<< orphan*/  iovs_len; int /*<<< orphan*/  iovs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IOV ; 
 int cloudabi32_copyinuio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio**) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int kern_readv (struct thread*,int /*<<< orphan*/ ,struct uio*) ; 

int
cloudabi32_sys_fd_read(struct thread *td,
    struct cloudabi32_sys_fd_read_args *uap)
{
	struct uio *uio;
	int error;

	error = cloudabi32_copyinuio(uap->iovs, uap->iovs_len, &uio);
	if (error != 0)
		return (error);
	error = kern_readv(td, uap->fd, uio);
	free(uio, M_IOV);
	return (error);
}
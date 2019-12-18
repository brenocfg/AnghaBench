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
struct thread {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct linux_bind_args {int namelen; int /*<<< orphan*/  s; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int kern_bindat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int linux_to_bsd_sockaddr (int /*<<< orphan*/ ,struct sockaddr**,int*) ; 

int
linux_bind(struct thread *td, struct linux_bind_args *args)
{
	struct sockaddr *sa;
	int error;

	error = linux_to_bsd_sockaddr(PTRIN(args->name), &sa,
	    &args->namelen);
	if (error != 0)
		return (error);

	error = kern_bindat(td, AT_FDCWD, args->s, sa);
	free(sa, M_SONAME);

	/* XXX */
	if (error == EADDRNOTAVAIL && args->namelen != sizeof(struct sockaddr_in))
		return (EINVAL);
	return (error);
}
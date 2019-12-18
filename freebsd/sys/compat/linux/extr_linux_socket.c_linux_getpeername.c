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
typedef  int sockaddr ;
struct linux_getpeername_args {int /*<<< orphan*/  namelen; int /*<<< orphan*/  addr; int /*<<< orphan*/  s; } ;
typedef  int l_sockaddr ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int bsd_to_linux_sockaddr (int*,int**,int) ; 
 int copyin (int /*<<< orphan*/ ,int*,int) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int kern_getpeername (struct thread*,int /*<<< orphan*/ ,int**,int*) ; 

int
linux_getpeername(struct thread *td, struct linux_getpeername_args *args)
{
	struct l_sockaddr *lsa;
	struct sockaddr *sa;
	int len, error;

	error = copyin(PTRIN(args->namelen), &len, sizeof(len));
	if (error != 0)
		return (error);
	if (len < 0)
		return (EINVAL);

	error = kern_getpeername(td, args->s, &sa, &len);
	if (error != 0)
		return (error);

	if (len != 0) {
		error = bsd_to_linux_sockaddr(sa, &lsa, len);
		if (error == 0)
			error = copyout(lsa, PTRIN(args->addr),
			    len);
		free(lsa, M_SONAME);
	}

	free(sa, M_SONAME);
	if (error == 0)
		error = copyout(&len, PTRIN(args->namelen), sizeof(len));
	return (error);
}
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
typedef  int u_int ;
struct thread {int dummy; } ;
struct socket {int so_error; void* so_emuldata; } ;
struct sockaddr {int dummy; } ;
struct linux_connect_args {int /*<<< orphan*/  s; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct file {struct socket* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EISCONN ; 
 int FNONBLOCK ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  cap_connect_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int getsock_cap (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**,int*,int /*<<< orphan*/ *) ; 
 int kern_connectat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int linux_to_bsd_sockaddr (int /*<<< orphan*/ ,struct sockaddr**,int /*<<< orphan*/ *) ; 

int
linux_connect(struct thread *td, struct linux_connect_args *args)
{
	struct socket *so;
	struct sockaddr *sa;
	struct file *fp;
	u_int fflag;
	int error;

	error = linux_to_bsd_sockaddr(PTRIN(args->name), &sa,
	    &args->namelen);
	if (error != 0)
		return (error);

	error = kern_connectat(td, AT_FDCWD, args->s, sa);
	free(sa, M_SONAME);
	if (error != EISCONN)
		return (error);

	/*
	 * Linux doesn't return EISCONN the first time it occurs,
	 * when on a non-blocking socket. Instead it returns the
	 * error getsockopt(SOL_SOCKET, SO_ERROR) would return on BSD.
	 */
	error = getsock_cap(td, args->s, &cap_connect_rights,
	    &fp, &fflag, NULL);
	if (error != 0)
		return (error);

	error = EISCONN;
	so = fp->f_data;
	if (fflag & FNONBLOCK) {
		SOCK_LOCK(so);
		if (so->so_emuldata == 0)
			error = so->so_error;
		so->so_emuldata = (void *)1;
		SOCK_UNLOCK(so);
	}
	fdrop(fp, td);

	return (error);
}
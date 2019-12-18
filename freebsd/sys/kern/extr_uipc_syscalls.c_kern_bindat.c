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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct file {struct socket* f_data; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_SOCKADDR (struct thread*,int,struct sockaddr*) ; 
 int ECAPMODE ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_STRUCT ; 
 int /*<<< orphan*/  cap_bind_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getsock_cap (struct thread*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktrsockaddr (struct sockaddr*) ; 
 int mac_socket_check_bind (int /*<<< orphan*/ ,struct socket*,struct sockaddr*) ; 
 int sobind (struct socket*,struct sockaddr*,struct thread*) ; 
 int sobindat (int,struct socket*,struct sockaddr*,struct thread*) ; 

int
kern_bindat(struct thread *td, int dirfd, int fd, struct sockaddr *sa)
{
	struct socket *so;
	struct file *fp;
	int error;

#ifdef CAPABILITY_MODE
	if (IN_CAPABILITY_MODE(td) && (dirfd == AT_FDCWD))
		return (ECAPMODE);
#endif

	AUDIT_ARG_FD(fd);
	AUDIT_ARG_SOCKADDR(td, dirfd, sa);
	error = getsock_cap(td, fd, &cap_bind_rights,
	    &fp, NULL, NULL);
	if (error != 0)
		return (error);
	so = fp->f_data;
#ifdef KTRACE
	if (KTRPOINT(td, KTR_STRUCT))
		ktrsockaddr(sa);
#endif
#ifdef MAC
	error = mac_socket_check_bind(td->td_ucred, so, sa);
	if (error == 0) {
#endif
		if (dirfd == AT_FDCWD)
			error = sobind(so, sa, td);
		else
			error = sobindat(dirfd, so, sa, td);
#ifdef MAC
	}
#endif
	fdrop(fp, td);
	return (error);
}
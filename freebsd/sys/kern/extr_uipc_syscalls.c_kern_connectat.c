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
struct socket {int so_state; int so_error; int /*<<< orphan*/  so_lock; int /*<<< orphan*/  so_timeo; } ;
struct sockaddr {int dummy; } ;
struct file {struct socket* f_data; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_SOCKADDR (struct thread*,int,struct sockaddr*) ; 
 int EALREADY ; 
 int ECAPMODE ; 
 int EINPROGRESS ; 
 int EINTR ; 
 int ERESTART ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_STRUCT ; 
 int PCATCH ; 
 int PSOCK ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int SS_ISCONNECTING ; 
 int SS_NBIO ; 
 int /*<<< orphan*/  cap_connect_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getsock_cap (struct thread*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktrsockaddr (struct sockaddr*) ; 
 int mac_socket_check_connect (int /*<<< orphan*/ ,struct socket*,struct sockaddr*) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int soconnect (struct socket*,struct sockaddr*,struct thread*) ; 
 int soconnectat (int,struct socket*,struct sockaddr*,struct thread*) ; 

int
kern_connectat(struct thread *td, int dirfd, int fd, struct sockaddr *sa)
{
	struct socket *so;
	struct file *fp;
	int error, interrupted = 0;

#ifdef CAPABILITY_MODE
	if (IN_CAPABILITY_MODE(td) && (dirfd == AT_FDCWD))
		return (ECAPMODE);
#endif

	AUDIT_ARG_FD(fd);
	AUDIT_ARG_SOCKADDR(td, dirfd, sa);
	error = getsock_cap(td, fd, &cap_connect_rights,
	    &fp, NULL, NULL);
	if (error != 0)
		return (error);
	so = fp->f_data;
	if (so->so_state & SS_ISCONNECTING) {
		error = EALREADY;
		goto done1;
	}
#ifdef KTRACE
	if (KTRPOINT(td, KTR_STRUCT))
		ktrsockaddr(sa);
#endif
#ifdef MAC
	error = mac_socket_check_connect(td->td_ucred, so, sa);
	if (error != 0)
		goto bad;
#endif
	if (dirfd == AT_FDCWD)
		error = soconnect(so, sa, td);
	else
		error = soconnectat(dirfd, so, sa, td);
	if (error != 0)
		goto bad;
	if ((so->so_state & SS_NBIO) && (so->so_state & SS_ISCONNECTING)) {
		error = EINPROGRESS;
		goto done1;
	}
	SOCK_LOCK(so);
	while ((so->so_state & SS_ISCONNECTING) && so->so_error == 0) {
		error = msleep(&so->so_timeo, &so->so_lock, PSOCK | PCATCH,
		    "connec", 0);
		if (error != 0) {
			if (error == EINTR || error == ERESTART)
				interrupted = 1;
			break;
		}
	}
	if (error == 0) {
		error = so->so_error;
		so->so_error = 0;
	}
	SOCK_UNLOCK(so);
bad:
	if (!interrupted)
		so->so_state &= ~SS_ISCONNECTING;
	if (error == ERESTART)
		error = EINTR;
done1:
	fdrop(fp, td);
	return (error);
}
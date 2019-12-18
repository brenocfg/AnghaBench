#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct thread {int* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct socket {int so_options; int /*<<< orphan*/  so_sigio; TYPE_1__ so_rdsel; } ;
struct sockaddr {scalar_t__ sa_len; } ;
struct filecaps {int dummy; } ;
struct file {struct socket* f_data; } ;
typedef  scalar_t__ socklen_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int ACCEPT4_INHERIT ; 
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_SOCKADDR (struct thread*,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  DTYPE_SOCKET ; 
 int EINVAL ; 
 int FASYNC ; 
 int /*<<< orphan*/  FIOASYNC ; 
 int /*<<< orphan*/  FIONBIO ; 
 int FNONBLOCK ; 
 int /*<<< orphan*/  KNOTE_UNLOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_STRUCT ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int SOCK_CLOEXEC ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SOLISTENING (struct socket*) ; 
 int SO_ACCEPTCONN ; 
 int /*<<< orphan*/  cap_accept_rights ; 
 int falloc_caps (struct thread*,struct file**,int*,int /*<<< orphan*/ ,struct filecaps*) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 scalar_t__ fgetown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filecaps_free (struct filecaps*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fo_ioctl (struct file*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsetown (scalar_t__,int /*<<< orphan*/ *) ; 
 int getsock_cap (struct thread*,int,int /*<<< orphan*/ *,struct file**,int*,struct filecaps*) ; 
 int /*<<< orphan*/  ktrsockaddr (struct sockaddr*) ; 
 int mac_socket_check_accept (int /*<<< orphan*/ ,struct socket*) ; 
 int soaccept (struct socket*,struct sockaddr**) ; 
 int /*<<< orphan*/  socketops ; 
 int solisten_dequeue (struct socket*,struct socket**,int) ; 

int
kern_accept4(struct thread *td, int s, struct sockaddr **name,
    socklen_t *namelen, int flags, struct file **fp)
{
	struct file *headfp, *nfp = NULL;
	struct sockaddr *sa = NULL;
	struct socket *head, *so;
	struct filecaps fcaps;
	u_int fflag;
	pid_t pgid;
	int error, fd, tmp;

	if (name != NULL)
		*name = NULL;

	AUDIT_ARG_FD(s);
	error = getsock_cap(td, s, &cap_accept_rights,
	    &headfp, &fflag, &fcaps);
	if (error != 0)
		return (error);
	head = headfp->f_data;
	if ((head->so_options & SO_ACCEPTCONN) == 0) {
		error = EINVAL;
		goto done;
	}
#ifdef MAC
	error = mac_socket_check_accept(td->td_ucred, head);
	if (error != 0)
		goto done;
#endif
	error = falloc_caps(td, &nfp, &fd,
	    (flags & SOCK_CLOEXEC) ? O_CLOEXEC : 0, &fcaps);
	if (error != 0)
		goto done;
	SOCK_LOCK(head);
	if (!SOLISTENING(head)) {
		SOCK_UNLOCK(head);
		error = EINVAL;
		goto noconnection;
	}

	error = solisten_dequeue(head, &so, flags);
	if (error != 0)
		goto noconnection;

	/* An extra reference on `nfp' has been held for us by falloc(). */
	td->td_retval[0] = fd;

	/* Connection has been removed from the listen queue. */
	KNOTE_UNLOCKED(&head->so_rdsel.si_note, 0);

	if (flags & ACCEPT4_INHERIT) {
		pgid = fgetown(&head->so_sigio);
		if (pgid != 0)
			fsetown(pgid, &so->so_sigio);
	} else {
		fflag &= ~(FNONBLOCK | FASYNC);
		if (flags & SOCK_NONBLOCK)
			fflag |= FNONBLOCK;
	}

	finit(nfp, fflag, DTYPE_SOCKET, so, &socketops);
	/* Sync socket nonblocking/async state with file flags */
	tmp = fflag & FNONBLOCK;
	(void) fo_ioctl(nfp, FIONBIO, &tmp, td->td_ucred, td);
	tmp = fflag & FASYNC;
	(void) fo_ioctl(nfp, FIOASYNC, &tmp, td->td_ucred, td);
	error = soaccept(so, &sa);
	if (error != 0)
		goto noconnection;
	if (sa == NULL) {
		if (name)
			*namelen = 0;
		goto done;
	}
	AUDIT_ARG_SOCKADDR(td, AT_FDCWD, sa);
	if (name) {
		/* check sa_len before it is destroyed */
		if (*namelen > sa->sa_len)
			*namelen = sa->sa_len;
#ifdef KTRACE
		if (KTRPOINT(td, KTR_STRUCT))
			ktrsockaddr(sa);
#endif
		*name = sa;
		sa = NULL;
	}
noconnection:
	free(sa, M_SONAME);

	/*
	 * close the new descriptor, assuming someone hasn't ripped it
	 * out from under us.
	 */
	if (error != 0)
		fdclose(td, nfp, fd);

	/*
	 * Release explicitly held references before returning.  We return
	 * a reference on nfp to the caller on success if they request it.
	 */
done:
	if (nfp == NULL)
		filecaps_free(&fcaps);
	if (fp != NULL) {
		if (error == 0) {
			*fp = nfp;
			nfp = NULL;
		} else
			*fp = NULL;
	}
	if (nfp != NULL)
		fdrop(nfp, td);
	fdrop(headfp, td);
	return (error);
}
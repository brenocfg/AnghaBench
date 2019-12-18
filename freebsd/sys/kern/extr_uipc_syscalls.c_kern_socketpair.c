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
struct unpcb {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {TYPE_1__* so_proto; } ;
struct file {struct socket* f_data; } ;
struct TYPE_2__ {int pr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_SOCKET (int,int,int) ; 
 int /*<<< orphan*/  DTYPE_SOCKET ; 
 int /*<<< orphan*/  FIONBIO ; 
 int FNONBLOCK ; 
 int FREAD ; 
 int FWRITE ; 
 int O_CLOEXEC ; 
 int PR_CONNREQUIRED ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int SOCK_NONBLOCK ; 
 int falloc (struct thread*,struct file**,int*,int) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fo_ioctl (struct file*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct thread*) ; 
 int mac_socket_check_create (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  socketops ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int soconnect2 (struct socket*,struct socket*) ; 
 int socreate (int,struct socket**,int,int,int /*<<< orphan*/ ,struct thread*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_copy_peercred (struct thread*,struct unpcb*,struct unpcb*,struct unpcb*) ; 

int
kern_socketpair(struct thread *td, int domain, int type, int protocol,
    int *rsv)
{
	struct file *fp1, *fp2;
	struct socket *so1, *so2;
	int fd, error, oflag, fflag;

	AUDIT_ARG_SOCKET(domain, type, protocol);

	oflag = 0;
	fflag = 0;
	if ((type & SOCK_CLOEXEC) != 0) {
		type &= ~SOCK_CLOEXEC;
		oflag |= O_CLOEXEC;
	}
	if ((type & SOCK_NONBLOCK) != 0) {
		type &= ~SOCK_NONBLOCK;
		fflag |= FNONBLOCK;
	}
#ifdef MAC
	/* We might want to have a separate check for socket pairs. */
	error = mac_socket_check_create(td->td_ucred, domain, type,
	    protocol);
	if (error != 0)
		return (error);
#endif
	error = socreate(domain, &so1, type, protocol, td->td_ucred, td);
	if (error != 0)
		return (error);
	error = socreate(domain, &so2, type, protocol, td->td_ucred, td);
	if (error != 0)
		goto free1;
	/* On success extra reference to `fp1' and 'fp2' is set by falloc. */
	error = falloc(td, &fp1, &fd, oflag);
	if (error != 0)
		goto free2;
	rsv[0] = fd;
	fp1->f_data = so1;	/* so1 already has ref count */
	error = falloc(td, &fp2, &fd, oflag);
	if (error != 0)
		goto free3;
	fp2->f_data = so2;	/* so2 already has ref count */
	rsv[1] = fd;
	error = soconnect2(so1, so2);
	if (error != 0)
		goto free4;
	if (type == SOCK_DGRAM) {
		/*
		 * Datagram socket connection is asymmetric.
		 */
		 error = soconnect2(so2, so1);
		 if (error != 0)
			goto free4;
	} else if (so1->so_proto->pr_flags & PR_CONNREQUIRED) {
		struct unpcb *unp, *unp2;
		unp = sotounpcb(so1);
		unp2 = sotounpcb(so2);
		/* 
		 * No need to lock the unps, because the sockets are brand-new.
		 * No other threads can be using them yet
		 */
		unp_copy_peercred(td, unp, unp2, unp);
	}
	finit(fp1, FREAD | FWRITE | fflag, DTYPE_SOCKET, fp1->f_data,
	    &socketops);
	finit(fp2, FREAD | FWRITE | fflag, DTYPE_SOCKET, fp2->f_data,
	    &socketops);
	if ((fflag & FNONBLOCK) != 0) {
		(void) fo_ioctl(fp1, FIONBIO, &fflag, td->td_ucred, td);
		(void) fo_ioctl(fp2, FIONBIO, &fflag, td->td_ucred, td);
	}
	fdrop(fp1, td);
	fdrop(fp2, td);
	return (0);
free4:
	fdclose(td, fp2, rsv[1]);
	fdrop(fp2, td);
free3:
	fdclose(td, fp1, rsv[0]);
	fdrop(fp1, td);
free2:
	if (so2 != NULL)
		(void)soclose(so2);
free1:
	if (so1 != NULL)
		(void)soclose(so1);
	return (error);
}
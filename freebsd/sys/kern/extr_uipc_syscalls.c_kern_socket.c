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
struct thread {int* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_SOCKET (int,int,int) ; 
 int /*<<< orphan*/  DTYPE_SOCKET ; 
 int /*<<< orphan*/  FIONBIO ; 
 int FNONBLOCK ; 
 int FREAD ; 
 int FWRITE ; 
 int O_CLOEXEC ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int falloc (struct thread*,struct file**,int*,int) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fo_ioctl (struct file*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct thread*) ; 
 int mac_socket_check_create (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  socketops ; 
 int socreate (int,struct socket**,int,int,int /*<<< orphan*/ ,struct thread*) ; 

int
kern_socket(struct thread *td, int domain, int type, int protocol)
{
	struct socket *so;
	struct file *fp;
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
	error = mac_socket_check_create(td->td_ucred, domain, type, protocol);
	if (error != 0)
		return (error);
#endif
	error = falloc(td, &fp, &fd, oflag);
	if (error != 0)
		return (error);
	/* An extra reference on `fp' has been held for us by falloc(). */
	error = socreate(domain, &so, type, protocol, td->td_ucred, td);
	if (error != 0) {
		fdclose(td, fp, fd);
	} else {
		finit(fp, FREAD | FWRITE | fflag, DTYPE_SOCKET, so, &socketops);
		if ((fflag & FNONBLOCK) != 0)
			(void) fo_ioctl(fp, FIONBIO, &fflag, td->td_ucred, td);
		td->td_retval[0] = fd;
	}
	fdrop(fp, td);
	return (error);
}
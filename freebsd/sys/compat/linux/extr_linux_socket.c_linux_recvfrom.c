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
struct msghdr {int* msg_name; int msg_namelen; int msg_iovlen; int /*<<< orphan*/  msg_flags; scalar_t__ msg_control; struct iovec* msg_iov; } ;
struct linux_recvfrom_args {int /*<<< orphan*/  fromlen; int /*<<< orphan*/  from; int /*<<< orphan*/  s; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  int l_sockaddr ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  fromlen ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int bsd_to_linux_sockaddr (int*,int**,int) ; 
 int copyin (int /*<<< orphan*/ *,int*,int) ; 
 int copyout (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int kern_recvit (struct thread*,int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_to_bsd_msg_flags (int /*<<< orphan*/ ) ; 
 int* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_recvfrom(struct thread *td, struct linux_recvfrom_args *args)
{
	struct l_sockaddr *lsa;
	struct sockaddr *sa;
	struct msghdr msg;
	struct iovec aiov;
	int error, fromlen;

	if (PTRIN(args->fromlen) != NULL) {
		error = copyin(PTRIN(args->fromlen), &fromlen,
		    sizeof(fromlen));
		if (error != 0)
			return (error);
		if (fromlen < 0)
			return (EINVAL);
		sa = malloc(fromlen, M_SONAME, M_WAITOK);
	} else {
		fromlen = 0;
		sa = NULL;
	}

	msg.msg_name = sa;
	msg.msg_namelen = fromlen;
	msg.msg_iov = &aiov;
	msg.msg_iovlen = 1;
	aiov.iov_base = PTRIN(args->buf);
	aiov.iov_len = args->len;
	msg.msg_control = 0;
	msg.msg_flags = linux_to_bsd_msg_flags(args->flags);

	error = kern_recvit(td, args->s, &msg, UIO_SYSSPACE, NULL);
	if (error != 0)
		goto out;

	if (PTRIN(args->from) != NULL) {
		error = bsd_to_linux_sockaddr(sa, &lsa, msg.msg_namelen);
		if (error == 0)
			error = copyout(lsa, PTRIN(args->from),
			    msg.msg_namelen);
		free(lsa, M_SONAME);
	}

	if (error == 0 && PTRIN(args->fromlen) != NULL)
		error = copyout(&msg.msg_namelen, PTRIN(args->fromlen),
		    sizeof(msg.msg_namelen));
out:
	free(sa, M_SONAME);
	return (error);
}
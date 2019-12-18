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
struct thread {int /*<<< orphan*/  td_proc; } ;
struct recvmsg_args {int /*<<< orphan*/  msg; int /*<<< orphan*/  s; int /*<<< orphan*/  flags; } ;
struct msghdr {struct iovec* msg_iov; int /*<<< orphan*/  msg_flags; int /*<<< orphan*/  msg_iovlen; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  MSG_COMPAT ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  SV_AOUT ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int copyiniov (struct iovec*,int /*<<< orphan*/ ,struct iovec**,int /*<<< orphan*/ ) ; 
 int copyout (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 int recvit (struct thread*,int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ *) ; 

int
sys_recvmsg(struct thread *td, struct recvmsg_args *uap)
{
	struct msghdr msg;
	struct iovec *uiov, *iov;
	int error;

	error = copyin(uap->msg, &msg, sizeof (msg));
	if (error != 0)
		return (error);
	error = copyiniov(msg.msg_iov, msg.msg_iovlen, &iov, EMSGSIZE);
	if (error != 0)
		return (error);
	msg.msg_flags = uap->flags;
#ifdef COMPAT_OLDSOCK
	if (SV_PROC_FLAG(td->td_proc, SV_AOUT))
		msg.msg_flags &= ~MSG_COMPAT;
#endif
	uiov = msg.msg_iov;
	msg.msg_iov = iov;
	error = recvit(td, uap->s, &msg, NULL);
	if (error == 0) {
		msg.msg_iov = uiov;
		error = copyout(&msg, uap->msg, sizeof(msg));
	}
	free(iov, M_IOV);
	return (error);
}
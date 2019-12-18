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
struct timespec {scalar_t__ tv_sec; } ;
struct thread {int* td_retval; } ;
struct msghdr {int msg_flags; } ;
struct linux_recvmmsg_args {int vlen; int flags; scalar_t__ timeout; int /*<<< orphan*/  s; int /*<<< orphan*/  msg; } ;
struct l_timespec {int dummy; } ;
struct l_mmsghdr {int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg_hdr; } ;
typedef  int l_uint ;

/* Variables and functions */
 int LINUX_MSG_DONTWAIT ; 
 int LINUX_MSG_WAITFORONE ; 
 int MSG_OOB ; 
 struct l_mmsghdr* PTRIN (int /*<<< orphan*/ ) ; 
 int copyin (scalar_t__,struct l_timespec*,int) ; 
 int copyout (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int linux_recvmsg_common (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct msghdr*) ; 
 int linux_to_native_timespec (struct timespec*,struct l_timespec*) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timespecisset (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

int
linux_recvmmsg(struct thread *td, struct linux_recvmmsg_args *args)
{
	struct l_mmsghdr *msg;
	struct msghdr bsd_msg;
	struct l_timespec lts;
	struct timespec ts, tts;
	l_uint retval;
	int error, datagrams;

	if (args->timeout) {
		error = copyin(args->timeout, &lts, sizeof(struct l_timespec));
		if (error != 0)
			return (error);
		error = linux_to_native_timespec(&ts, &lts);
		if (error != 0)
			return (error);
		getnanotime(&tts);
		timespecadd(&tts, &ts, &tts);
	}

	msg = PTRIN(args->msg);
	datagrams = 0;
	while (datagrams < args->vlen) {
		error = linux_recvmsg_common(td, args->s, &msg->msg_hdr,
		    args->flags & ~LINUX_MSG_WAITFORONE, &bsd_msg);
		if (error != 0)
			break;

		retval = td->td_retval[0];
		error = copyout(&retval, &msg->msg_len, sizeof(msg->msg_len));
		if (error != 0)
			break;
		++msg;
		++datagrams;

		/*
		 * MSG_WAITFORONE turns on MSG_DONTWAIT after one packet.
		 */
		if (args->flags & LINUX_MSG_WAITFORONE)
			args->flags |= LINUX_MSG_DONTWAIT;

		/*
		 * See BUGS section of recvmmsg(2).
		 */
		if (args->timeout) {
			getnanotime(&ts);
			timespecsub(&ts, &tts, &ts);
			if (!timespecisset(&ts) || ts.tv_sec > 0)
				break;
		}
		/* Out of band data, return right away. */
		if (bsd_msg.msg_flags & MSG_OOB)
			break;
	}
	if (error == 0)
		td->td_retval[0] = datagrams;
	return (error);
}
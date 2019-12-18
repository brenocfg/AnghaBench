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
struct timespec {int dummy; } ;
struct pollfd {int fd; int revents; short events; } ;
struct mmsghdr {int msg_len; int /*<<< orphan*/  msg_hdr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MSG_DONTWAIT ; 
 int MSG_WAITFORONE ; 
 short POLLIN ; 
 int POLLNVAL ; 
 short POLLPRI ; 
 short POLLRDBAND ; 
 short POLLRDNORM ; 
 int __sys_recvmsg (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int ppoll (struct pollfd*,int,struct timespec const*,int /*<<< orphan*/ *) ; 

ssize_t
recvmmsg(int s, struct mmsghdr *__restrict msgvec, size_t vlen, int flags,
    const struct timespec *__restrict timeout)
{
	struct pollfd pfd[1];
	size_t i, rcvd;
	ssize_t ret;
	int res;
	short ev;

	if (timeout != NULL) {
		pfd[0].fd = s;
		pfd[0].revents = 0;
		pfd[0].events = ev = POLLIN | POLLRDNORM | POLLRDBAND |
		    POLLPRI;
		res = ppoll(&pfd[0], 1, timeout, NULL);
		if (res == -1 || res == 0)
			return (res);
		if (pfd[0].revents & POLLNVAL) {
			errno = EBADF;
			return (-1);
		}
		if ((pfd[0].revents & ev) == 0) {
			errno = ETIMEDOUT;
			return (-1);
		}
	}

	ret = __sys_recvmsg(s, &msgvec[0].msg_hdr, flags);
	if (ret == -1)
		return (ret);

	msgvec[0].msg_len = ret;

	/* 
	 * Do non-blocking receive for second and later messages if
	 * WAITFORONE is set.
	 */
	if (flags & MSG_WAITFORONE)
		flags |= MSG_DONTWAIT;

	rcvd = 1;
	for (i = rcvd; i < vlen; i++, rcvd++) {
		ret = __sys_recvmsg(s, &msgvec[i].msg_hdr, flags);
		if (ret == -1) {
			/* We have received messages. Let caller know
			 * about the data received, socket error is
			 * returned on next invocation.
			 */
			return (rcvd);
		}

		/* Save received bytes. */
		msgvec[i].msg_len = ret;
	}

	return (rcvd);
}
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
struct msghdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int MSG_CMSG_CLOEXEC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_wait (int,int) ; 
 int recvmsg (int,struct msghdr*,int) ; 

__attribute__((used)) static int
msg_recv(int sock, struct msghdr *msg)
{
	int flags;

	PJDLOG_ASSERT(sock >= 0);

#ifdef MSG_CMSG_CLOEXEC
	flags = MSG_CMSG_CLOEXEC;
#else
	flags = 0;
#endif

	for (;;) {
		fd_wait(sock, true);
		if (recvmsg(sock, msg, flags) == -1) {
			if (errno == EINTR)
				continue;
			return (-1);
		}
		break;
	}

	return (0);
}
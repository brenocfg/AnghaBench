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
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_wait (int,int) ; 
 int sendmsg (int,struct msghdr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msg_send(int sock, const struct msghdr *msg)
{

	PJDLOG_ASSERT(sock >= 0);

	for (;;) {
		fd_wait(sock, false);
		if (sendmsg(sock, msg, 0) == -1) {
			if (errno == EINTR)
				continue;
			return (-1);
		}
		break;
	}

	return (0);
}
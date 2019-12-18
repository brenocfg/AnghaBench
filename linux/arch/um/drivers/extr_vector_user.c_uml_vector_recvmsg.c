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
struct msghdr {int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int EAGAIN ; 
 int errno ; 
 int readv (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uml_vector_recvmsg(int fd, void *hdr, int flags)
{
	int n;
	struct msghdr *msg = (struct msghdr *) hdr;

	CATCH_EINTR(n = readv(fd, msg->msg_iov, msg->msg_iovlen));
	if ((n < 0) && (errno == EAGAIN))
		return 0;
	if (n >= 0)
		return n;
	else
		return -errno;
}
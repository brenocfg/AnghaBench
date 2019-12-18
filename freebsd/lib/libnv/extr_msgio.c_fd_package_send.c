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
typedef  scalar_t__ uint8_t ;
struct msghdr {int msg_iovlen; size_t msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; } ;
struct iovec {int iov_len; scalar_t__* iov_base; } ;
struct cmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 size_t CMSG_SPACE (int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  bzero (struct msghdr*,int) ; 
 int /*<<< orphan*/ * calloc (int,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int msg_send (int,struct msghdr*) ; 
 int msghdr_add_fd (struct cmsghdr*,int const) ; 

__attribute__((used)) static int
fd_package_send(int sock, const int *fds, size_t nfds)
{
	struct msghdr msg;
	struct cmsghdr *cmsg;
	struct iovec iov;
	unsigned int i;
	int serrno, ret;
	uint8_t dummy;

	PJDLOG_ASSERT(sock >= 0);
	PJDLOG_ASSERT(fds != NULL);
	PJDLOG_ASSERT(nfds > 0);

	bzero(&msg, sizeof(msg));

	/*
	 * XXX: Look into cred_send function for more details.
	 */
	dummy = 0;
	iov.iov_base = &dummy;
	iov.iov_len = sizeof(dummy);

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_controllen = nfds * CMSG_SPACE(sizeof(int));
	msg.msg_control = calloc(1, msg.msg_controllen);
	if (msg.msg_control == NULL)
		return (-1);

	ret = -1;

	for (i = 0, cmsg = CMSG_FIRSTHDR(&msg); i < nfds && cmsg != NULL;
	    i++, cmsg = CMSG_NXTHDR(&msg, cmsg)) {
		if (msghdr_add_fd(cmsg, fds[i]) == -1)
			goto end;
	}

	if (msg_send(sock, &msg) == -1)
		goto end;

	ret = 0;
end:
	serrno = errno;
	free(msg.msg_control);
	errno = serrno;
	return (ret);
}
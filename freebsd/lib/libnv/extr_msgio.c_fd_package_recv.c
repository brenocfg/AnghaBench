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
typedef  int /*<<< orphan*/  uint8_t ;
struct msghdr {int iov_len; int msg_iovlen; size_t msg_controllen; int /*<<< orphan*/ * msg_control; struct msghdr* msg_iov; int /*<<< orphan*/ * iov_base; } ;
struct iovec {int iov_len; int msg_iovlen; size_t msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; int /*<<< orphan*/ * iov_base; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; int cmsg_len; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  iov ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int CMSG_LEN (int /*<<< orphan*/ ) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 size_t CMSG_SPACE (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ SCM_RIGHTS ; 
 scalar_t__ SOL_SOCKET ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bzero (struct msghdr*,int) ; 
 int /*<<< orphan*/ * calloc (int,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int msg_recv (int,struct msghdr*) ; 

__attribute__((used)) static int
fd_package_recv(int sock, int *fds, size_t nfds)
{
	struct msghdr msg;
	struct cmsghdr *cmsg;
	unsigned int i;
	int serrno, ret;
	struct iovec iov;
	uint8_t dummy;

	PJDLOG_ASSERT(sock >= 0);
	PJDLOG_ASSERT(nfds > 0);
	PJDLOG_ASSERT(fds != NULL);

	bzero(&msg, sizeof(msg));
	bzero(&iov, sizeof(iov));

	/*
	 * XXX: Look into cred_send function for more details.
	 */
	iov.iov_base = &dummy;
	iov.iov_len = sizeof(dummy);

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_controllen = nfds * CMSG_SPACE(sizeof(int));
	msg.msg_control = calloc(1, msg.msg_controllen);
	if (msg.msg_control == NULL)
		return (-1);

	ret = -1;

	if (msg_recv(sock, &msg) == -1)
		goto end;

	i = 0;
	cmsg = CMSG_FIRSTHDR(&msg);
	while (cmsg && i < nfds) {
		unsigned int n;

		if (cmsg->cmsg_level != SOL_SOCKET ||
		    cmsg->cmsg_type != SCM_RIGHTS) {
			errno = EINVAL;
			break;
		}
		n = (cmsg->cmsg_len - CMSG_LEN(0)) / sizeof(int);
		if (i + n > nfds) {
			errno = EINVAL;
			break;
		}
		bcopy(CMSG_DATA(cmsg), fds + i, sizeof(int) * n);
		cmsg = CMSG_NXTHDR(&msg, cmsg);
		i += n;
	}

	if (cmsg != NULL || i < nfds) {
		unsigned int last;

		/*
		 * We need to close all received descriptors, even if we have
		 * different control message (eg. SCM_CREDS) in between.
		 */
		last = i;
		for (i = 0; i < last; i++) {
			if (fds[i] >= 0) {
				close(fds[i]);
			}
		}
		errno = EINVAL;
		goto end;
	}

#ifndef MSG_CMSG_CLOEXEC
	/*
	 * If the MSG_CMSG_CLOEXEC flag is not available we cannot set the
	 * close-on-exec flag atomically, but we still want to set it for
	 * consistency.
	 */
	for (i = 0; i < nfds; i++) {
		(void) fcntl(fds[i], F_SETFD, FD_CLOEXEC);
	}
#endif

	ret = 0;
end:
	serrno = errno;
	free(msg.msg_control);
	errno = serrno;
	return (ret);
}
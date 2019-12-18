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
struct ucred {int dummy; } ;
struct sockaddr_nl {int dummy; } ;
struct nl_sock {int s_flags; int /*<<< orphan*/  s_fd; } ;
struct msghdr {void* msg_name; int msg_namelen; int msg_iovlen; unsigned char* msg_control; int msg_controllen; int msg_flags; struct iovec* msg_iov; } ;
struct iovec {int iov_len; unsigned char* iov_base; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int CMSG_SPACE (int) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int MSG_CTRUNC ; 
 int MSG_PEEK ; 
 int MSG_TRUNC ; 
 int NLE_NOADDR ; 
 int /*<<< orphan*/  NL_DBG (int,char*) ; 
 int NL_MSG_PEEK ; 
 int NL_SOCK_PASSCRED ; 
 scalar_t__ SCM_CREDENTIALS ; 
 scalar_t__ SOL_SOCKET ; 
 void* calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int getpagesize () ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct ucred*,int /*<<< orphan*/ ,int) ; 
 int nl_syserr2nlerr (scalar_t__) ; 
 void* realloc (unsigned char*,int) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int) ; 

int nl_recv(struct nl_sock *sk, struct sockaddr_nl *nla,
	    unsigned char **buf, struct ucred **creds)
{
	int n;
	int flags = 0;
	static int page_size = 0;
	struct iovec iov;
	struct msghdr msg = {
		.msg_name = (void *) nla,
		.msg_namelen = sizeof(struct sockaddr_nl),
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0,
	};
	struct cmsghdr *cmsg;

	if (sk->s_flags & NL_MSG_PEEK)
		flags |= MSG_PEEK;

	if (page_size == 0)
		page_size = getpagesize() * 4;

	iov.iov_len = page_size;
	iov.iov_base = *buf = malloc(iov.iov_len);

	if (sk->s_flags & NL_SOCK_PASSCRED) {
		msg.msg_controllen = CMSG_SPACE(sizeof(struct ucred));
		msg.msg_control = calloc(1, msg.msg_controllen);
	}
retry:

	n = recvmsg(sk->s_fd, &msg, flags);
	if (!n)
		goto abort;
	else if (n < 0) {
		if (errno == EINTR) {
			NL_DBG(3, "recvmsg() returned EINTR, retrying\n");
			goto retry;
		} else if (errno == EAGAIN) {
			NL_DBG(3, "recvmsg() returned EAGAIN, aborting\n");
			goto abort;
		} else {
			free(msg.msg_control);
			free(*buf);
			return -nl_syserr2nlerr(errno);
		}
	}

	if (iov.iov_len < n ||
	    msg.msg_flags & MSG_TRUNC) {
		/* Provided buffer is not long enough, enlarge it
		 * and try again. */
		iov.iov_len *= 2;
		iov.iov_base = *buf = realloc(*buf, iov.iov_len);
		goto retry;
	} else if (msg.msg_flags & MSG_CTRUNC) {
		msg.msg_controllen *= 2;
		msg.msg_control = realloc(msg.msg_control, msg.msg_controllen);
		goto retry;
	} else if (flags != 0) {
		/* Buffer is big enough, do the actual reading */
		flags = 0;
		goto retry;
	}

	if (msg.msg_namelen != sizeof(struct sockaddr_nl)) {
		free(msg.msg_control);
		free(*buf);
		return -NLE_NOADDR;
	}

	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
		if (cmsg->cmsg_level == SOL_SOCKET &&
		    cmsg->cmsg_type == SCM_CREDENTIALS) {
			*creds = calloc(1, sizeof(struct ucred));
			memcpy(*creds, CMSG_DATA(cmsg), sizeof(struct ucred));
			break;
		}
	}

	free(msg.msg_control);
	return n;

abort:
	free(msg.msg_control);
	free(*buf);
	return 0;
}
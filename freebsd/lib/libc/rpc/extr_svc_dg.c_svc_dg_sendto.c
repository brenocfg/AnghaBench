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
struct in_addr {scalar_t__ s_addr; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct msghdr {int msg_iovlen; char* msg_name; void* msg_controllen; scalar_t__ msg_control; int /*<<< orphan*/  msg_namelen; struct iovec* msg_iov; } ;
struct iovec {char* iov_base; int iov_len; } ;
struct cmsghdr {int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; void* cmsg_len; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 void* CMSG_LEN (int) ; 
 int CMSG_SPACE (int) ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_SENDSRCADDR ; 
 int _sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct in_addr*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
svc_dg_sendto(int fd, char *buf, int buflen,
    const struct sockaddr *raddr, socklen_t raddrlen,
    const struct sockaddr *laddr, socklen_t laddrlen)
{
	struct msghdr msg;
	struct iovec msg_iov[1];
	struct sockaddr_in *laddr_in = (struct sockaddr_in *)laddr;
	struct in_addr *lin = &laddr_in->sin_addr;
	char tmp[CMSG_SPACE(sizeof(*lin))];
	struct cmsghdr *cmsg;

	memset((char *)&msg, 0, sizeof(msg));
	msg_iov[0].iov_base = buf;
	msg_iov[0].iov_len = buflen;
	msg.msg_iov = msg_iov;
	msg.msg_iovlen = 1;
	msg.msg_namelen = raddrlen;
	msg.msg_name = (char *)raddr;

	if (laddr != NULL && laddr->sa_family == AF_INET &&
	    lin->s_addr != INADDR_ANY) {
		msg.msg_control = (caddr_t)tmp;
		msg.msg_controllen = CMSG_LEN(sizeof(*lin));
		cmsg = CMSG_FIRSTHDR(&msg);
		cmsg->cmsg_len = CMSG_LEN(sizeof(*lin));
		cmsg->cmsg_level = IPPROTO_IP;
		cmsg->cmsg_type = IP_SENDSRCADDR;
		memcpy(CMSG_DATA(cmsg), lin, sizeof(*lin));
	}

	return _sendmsg(fd, &msg, 0);
}
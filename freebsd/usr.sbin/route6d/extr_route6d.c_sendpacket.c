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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct msghdr {int msg_namelen; int msg_iovlen; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; scalar_t__ msg_flags; struct iovec* msg_iov; void* msg_name; } ;
struct iovec {int iov_len; void* iov_base; } ;
struct in6_pktinfo {int ipi6_ifindex; int /*<<< orphan*/  ipi6_addr; } ;
struct cmsghdr {int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; int /*<<< orphan*/  cmsg_len; } ;
typedef  int /*<<< orphan*/  cmsgbuf ;
typedef  void* caddr_t ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 scalar_t__ CMSG_SPACE (int) ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int errno ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ripbuf ; 
 int /*<<< orphan*/  ripsock ; 
 scalar_t__ sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  trace (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sendpacket(struct sockaddr_in6 *sin6, int len)
{
	struct msghdr m;
	struct cmsghdr *cm;
	struct iovec iov[2];
	struct in6_pktinfo *pi;
	u_char cmsgbuf[256];
	int idx;
	struct sockaddr_in6 sincopy;

	/* do not overwrite the given sin */
	sincopy = *sin6;
	sin6 = &sincopy;

	if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr) ||
	    IN6_IS_ADDR_MULTICAST(&sin6->sin6_addr))
		idx = sin6->sin6_scope_id;
	else
		idx = 0;

	m.msg_name = (caddr_t)sin6;
	m.msg_namelen = sizeof(*sin6);
	iov[0].iov_base = (caddr_t)ripbuf;
	iov[0].iov_len = len;
	m.msg_iov = iov;
	m.msg_iovlen = 1;
	m.msg_flags = 0;
	if (!idx) {
		m.msg_control = NULL;
		m.msg_controllen = 0;
	} else {
		memset(cmsgbuf, 0, sizeof(cmsgbuf));
		cm = (struct cmsghdr *)(void *)cmsgbuf;
		m.msg_control = (caddr_t)cm;
		m.msg_controllen = CMSG_SPACE(sizeof(struct in6_pktinfo));

		cm->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
		cm->cmsg_level = IPPROTO_IPV6;
		cm->cmsg_type = IPV6_PKTINFO;
		pi = (struct in6_pktinfo *)(void *)CMSG_DATA(cm);
		memset(&pi->ipi6_addr, 0, sizeof(pi->ipi6_addr)); /*::*/
		pi->ipi6_ifindex = idx;
	}

	if (sendmsg(ripsock, &m, 0 /*MSG_DONTROUTE*/) < 0) {
		trace(1, "sendmsg: %s\n", strerror(errno));
		return errno;
	}

	return 0;
}
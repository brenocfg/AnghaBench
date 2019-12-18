#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int nanoseconds; int /*<<< orphan*/  seconds; } ;
struct TYPE_4__ {struct cmsghdr* ipi6_ifindex; } ;
struct msghdr {int msg_flags; unsigned int msg_controllen; int /*<<< orphan*/  attributes; TYPE_1__ timestamp; TYPE_2__ pktinfo; int /*<<< orphan*/ * msg_control; } ;
struct in6_pktinfo {int /*<<< orphan*/  ipi6_addr; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  struct msghdr isc_socketevent_t ;
typedef  struct msghdr isc__socket_t ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ IPV6_PKTINFO ; 
 int /*<<< orphan*/  ISC_MSGSET_SOCKET ; 
 int /*<<< orphan*/  ISC_MSG_IFRECEIVED ; 
 int /*<<< orphan*/  ISC_MSG_PROCESSCMSG ; 
 int /*<<< orphan*/  ISC_SOCKEVENTATTR_CTRUNC ; 
 int /*<<< orphan*/  ISC_SOCKEVENTATTR_MULTICAST ; 
 int /*<<< orphan*/  ISC_SOCKEVENTATTR_PKTINFO ; 
 int /*<<< orphan*/  ISC_SOCKEVENTATTR_TIMESTAMP ; 
 int /*<<< orphan*/  ISC_SOCKEVENTATTR_TRUNC ; 
 int MSG_CTRUNC ; 
 int MSG_TRUNC ; 
 scalar_t__ SCM_TIMESTAMP ; 
 scalar_t__ SOL_SOCKET ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  UNUSED (struct msghdr*) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct in6_pktinfo*,int) ; 
 int /*<<< orphan*/  socket_log (struct msghdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmsghdr*) ; 

__attribute__((used)) static void
process_cmsg(isc__socket_t *sock, struct msghdr *msg, isc_socketevent_t *dev) {
#ifdef USE_CMSG
	struct cmsghdr *cmsgp;
#ifdef ISC_PLATFORM_HAVEIN6PKTINFO
	struct in6_pktinfo *pktinfop;
#endif
#ifdef SO_TIMESTAMP
	struct timeval *timevalp;
#endif
#endif

	/*
	 * sock is used only when ISC_NET_BSD44MSGHDR and USE_CMSG are defined.
	 * msg and dev are used only when ISC_NET_BSD44MSGHDR is defined.
	 * They are all here, outside of the CPP tests, because it is
	 * more consistent with the usual ISC coding style.
	 */
	UNUSED(sock);
	UNUSED(msg);
	UNUSED(dev);

#ifdef ISC_NET_BSD44MSGHDR

#ifdef MSG_TRUNC
	if ((msg->msg_flags & MSG_TRUNC) == MSG_TRUNC)
		dev->attributes |= ISC_SOCKEVENTATTR_TRUNC;
#endif

#ifdef MSG_CTRUNC
	if ((msg->msg_flags & MSG_CTRUNC) == MSG_CTRUNC)
		dev->attributes |= ISC_SOCKEVENTATTR_CTRUNC;
#endif

#ifndef USE_CMSG
	return;
#else
	if (msg->msg_controllen == 0U || msg->msg_control == NULL)
		return;

#ifdef SO_TIMESTAMP
	timevalp = NULL;
#endif
#ifdef ISC_PLATFORM_HAVEIN6PKTINFO
	pktinfop = NULL;
#endif

	cmsgp = CMSG_FIRSTHDR(msg);
	while (cmsgp != NULL) {
		socket_log(sock, NULL, TRACE,
			   isc_msgcat, ISC_MSGSET_SOCKET, ISC_MSG_PROCESSCMSG,
			   "processing cmsg %p", cmsgp);

#ifdef ISC_PLATFORM_HAVEIN6PKTINFO
		if (cmsgp->cmsg_level == IPPROTO_IPV6
		    && cmsgp->cmsg_type == IPV6_PKTINFO) {

			pktinfop = (struct in6_pktinfo *)CMSG_DATA(cmsgp);
			memcpy(&dev->pktinfo, pktinfop,
			       sizeof(struct in6_pktinfo));
			dev->attributes |= ISC_SOCKEVENTATTR_PKTINFO;
			socket_log(sock, NULL, TRACE,
				   isc_msgcat, ISC_MSGSET_SOCKET,
				   ISC_MSG_IFRECEIVED,
				   "interface received on ifindex %u",
				   dev->pktinfo.ipi6_ifindex);
			if (IN6_IS_ADDR_MULTICAST(&pktinfop->ipi6_addr))
				dev->attributes |= ISC_SOCKEVENTATTR_MULTICAST;
			goto next;
		}
#endif

#ifdef SO_TIMESTAMP
		if (cmsgp->cmsg_level == SOL_SOCKET
		    && cmsgp->cmsg_type == SCM_TIMESTAMP) {
			timevalp = (struct timeval *)CMSG_DATA(cmsgp);
			dev->timestamp.seconds = timevalp->tv_sec;
			dev->timestamp.nanoseconds = timevalp->tv_usec * 1000;
			dev->attributes |= ISC_SOCKEVENTATTR_TIMESTAMP;
			goto next;
		}
#endif

	next:
		cmsgp = CMSG_NXTHDR(msg, cmsgp);
	}
#endif /* USE_CMSG */

#endif /* ISC_NET_BSD44MSGHDR */
}
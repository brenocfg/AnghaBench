#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  use_min_mtu ;
struct msghdr {unsigned int msg_iovlen; scalar_t__ msg_controllen; scalar_t__ msg_accrightslen; int /*<<< orphan*/ * msg_accrights; int /*<<< orphan*/ * msg_control; scalar_t__ msg_flags; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
struct in6_pktinfo {int dummy; } ;
struct cmsghdr {void* cmsg_len; int /*<<< orphan*/  cmsg_type; void* cmsg_level; } ;
struct TYPE_13__ {size_t length; scalar_t__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  sa; } ;
struct TYPE_12__ {scalar_t__ length; TYPE_1__ type; } ;
struct TYPE_14__ {size_t n; int attributes; int pktinfo; TYPE_3__ region; int /*<<< orphan*/  bufferlist; TYPE_2__ address; } ;
typedef  TYPE_4__ isc_socketevent_t ;
struct TYPE_15__ {size_t length; scalar_t__ base; } ;
typedef  TYPE_5__ isc_region_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ sendcmsgbuflen; scalar_t__ sendcmsgbuf; int /*<<< orphan*/  connected; } ;
typedef  TYPE_6__ isc__socket_t ;

/* Variables and functions */
 struct in6_pktinfo* CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 void* IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int /*<<< orphan*/  IPV6_USE_MIN_MTU ; 
 int /*<<< orphan*/  ISC_BUFFER_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ISC_LIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_MSGSET_SOCKET ; 
 int /*<<< orphan*/  ISC_MSG_SENDTODATA ; 
 int ISC_SOCKEVENTATTR_PKTINFO ; 
 unsigned int MAXSCATTERGATHER_SEND ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 void* cmsg_len (int) ; 
 scalar_t__ cmsg_space (int) ; 
 size_t isc_buffer_usedlength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_usedregion (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 scalar_t__ isc_sockettype_udp ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memcpy (struct in6_pktinfo*,int*,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_log (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_msghdr_send(isc__socket_t *sock, isc_socketevent_t *dev,
		  struct msghdr *msg, struct iovec *iov, size_t *write_countp)
{
	unsigned int iovcount;
	isc_buffer_t *buffer;
	isc_region_t used;
	size_t write_count;
	size_t skip_count;

	memset(msg, 0, sizeof(*msg));

	if (!sock->connected) {
		msg->msg_name = (void *)&dev->address.type.sa;
		msg->msg_namelen = dev->address.length;
	} else {
		msg->msg_name = NULL;
		msg->msg_namelen = 0;
	}

	buffer = ISC_LIST_HEAD(dev->bufferlist);
	write_count = 0;
	iovcount = 0;

	/*
	 * Single buffer I/O?  Skip what we've done so far in this region.
	 */
	if (buffer == NULL) {
		write_count = dev->region.length - dev->n;
		iov[0].iov_base = (void *)(dev->region.base + dev->n);
		iov[0].iov_len = write_count;
		iovcount = 1;

		goto config;
	}

	/*
	 * Multibuffer I/O.
	 * Skip the data in the buffer list that we have already written.
	 */
	skip_count = dev->n;
	while (buffer != NULL) {
		REQUIRE(ISC_BUFFER_VALID(buffer));
		if (skip_count < isc_buffer_usedlength(buffer))
			break;
		skip_count -= isc_buffer_usedlength(buffer);
		buffer = ISC_LIST_NEXT(buffer, link);
	}

	while (buffer != NULL) {
		INSIST(iovcount < MAXSCATTERGATHER_SEND);

		isc_buffer_usedregion(buffer, &used);

		if (used.length > 0) {
			iov[iovcount].iov_base = (void *)(used.base
							  + skip_count);
			iov[iovcount].iov_len = used.length - skip_count;
			write_count += (used.length - skip_count);
			skip_count = 0;
			iovcount++;
		}
		buffer = ISC_LIST_NEXT(buffer, link);
	}

	INSIST(skip_count == 0U);

 config:
	msg->msg_iov = iov;
	msg->msg_iovlen = iovcount;

#ifdef ISC_NET_BSD44MSGHDR
	msg->msg_control = NULL;
	msg->msg_controllen = 0;
	msg->msg_flags = 0;
#if defined(USE_CMSG) && defined(ISC_PLATFORM_HAVEIN6PKTINFO)
	if ((sock->type == isc_sockettype_udp)
	    && ((dev->attributes & ISC_SOCKEVENTATTR_PKTINFO) != 0)) {
#if defined(IPV6_USE_MIN_MTU)
		int use_min_mtu = 1;	/* -1, 0, 1 */
#endif
		struct cmsghdr *cmsgp;
		struct in6_pktinfo *pktinfop;

		socket_log(sock, NULL, TRACE,
			   isc_msgcat, ISC_MSGSET_SOCKET, ISC_MSG_SENDTODATA,
			   "sendto pktinfo data, ifindex %u",
			   dev->pktinfo.ipi6_ifindex);

		msg->msg_controllen = cmsg_space(sizeof(struct in6_pktinfo));
		INSIST(msg->msg_controllen <= sock->sendcmsgbuflen);
		msg->msg_control = (void *)sock->sendcmsgbuf;

		cmsgp = (struct cmsghdr *)sock->sendcmsgbuf;
		cmsgp->cmsg_level = IPPROTO_IPV6;
		cmsgp->cmsg_type = IPV6_PKTINFO;
		cmsgp->cmsg_len = cmsg_len(sizeof(struct in6_pktinfo));
		pktinfop = (struct in6_pktinfo *)CMSG_DATA(cmsgp);
		memcpy(pktinfop, &dev->pktinfo, sizeof(struct in6_pktinfo));
#if defined(IPV6_USE_MIN_MTU)
		/*
		 * Set IPV6_USE_MIN_MTU as a per packet option as FreeBSD
		 * ignores setsockopt(IPV6_USE_MIN_MTU) when IPV6_PKTINFO
		 * is used.
		 */
		cmsgp = (struct cmsghdr *)(sock->sendcmsgbuf +
					   msg->msg_controllen);
		msg->msg_controllen += cmsg_space(sizeof(use_min_mtu));
		INSIST(msg->msg_controllen <= sock->sendcmsgbuflen);

		cmsgp->cmsg_level = IPPROTO_IPV6;
		cmsgp->cmsg_type = IPV6_USE_MIN_MTU;
		cmsgp->cmsg_len = cmsg_len(sizeof(use_min_mtu));
		memcpy(CMSG_DATA(cmsgp), &use_min_mtu, sizeof(use_min_mtu));
#endif
	}
#endif /* USE_CMSG && ISC_PLATFORM_HAVEIPV6 */
#else /* ISC_NET_BSD44MSGHDR */
	msg->msg_accrights = NULL;
	msg->msg_accrightslen = 0;
#endif /* ISC_NET_BSD44MSGHDR */

	if (write_countp != NULL)
		*write_countp = write_count;
}
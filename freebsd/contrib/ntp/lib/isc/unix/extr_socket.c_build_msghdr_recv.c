#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sa; int /*<<< orphan*/  sunix; int /*<<< orphan*/  sin6; int /*<<< orphan*/  sin; } ;
struct msghdr {int msg_namelen; unsigned int msg_iovlen; scalar_t__ msg_accrightslen; int /*<<< orphan*/ * msg_accrights; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; scalar_t__ msg_flags; struct iovec* msg_iov; int /*<<< orphan*/ * msg_name; TYPE_1__ type; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
struct TYPE_10__ {size_t length; size_t base; } ;
struct TYPE_11__ {size_t n; TYPE_2__ region; int /*<<< orphan*/  bufferlist; struct msghdr address; } ;
typedef  TYPE_3__ isc_socketevent_t ;
struct TYPE_12__ {size_t length; scalar_t__ base; } ;
typedef  TYPE_4__ isc_region_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;
struct TYPE_13__ {scalar_t__ type; scalar_t__ pf; scalar_t__ recvcmsgbuflen; int /*<<< orphan*/ * recvcmsgbuf; int /*<<< orphan*/  overflow; struct msghdr peer_address; } ;
typedef  TYPE_5__ isc__socket_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_BUFFER_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ISC_LIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MAXSCATTERGATHER_RECV ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_buffer_availablelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_availableregion (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ isc_sockettype_udp ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  maxiov ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
build_msghdr_recv(isc__socket_t *sock, isc_socketevent_t *dev,
		  struct msghdr *msg, struct iovec *iov, size_t *read_countp)
{
	unsigned int iovcount;
	isc_buffer_t *buffer;
	isc_region_t available;
	size_t read_count;

	memset(msg, 0, sizeof(struct msghdr));

	if (sock->type == isc_sockettype_udp) {
		memset(&dev->address, 0, sizeof(dev->address));
#ifdef BROKEN_RECVMSG
		if (sock->pf == AF_INET) {
			msg->msg_name = (void *)&dev->address.type.sin;
			msg->msg_namelen = sizeof(dev->address.type.sin6);
		} else if (sock->pf == AF_INET6) {
			msg->msg_name = (void *)&dev->address.type.sin6;
			msg->msg_namelen = sizeof(dev->address.type.sin6);
#ifdef ISC_PLATFORM_HAVESYSUNH
		} else if (sock->pf == AF_UNIX) {
			msg->msg_name = (void *)&dev->address.type.sunix;
			msg->msg_namelen = sizeof(dev->address.type.sunix);
#endif
		} else {
			msg->msg_name = (void *)&dev->address.type.sa;
			msg->msg_namelen = sizeof(dev->address.type);
		}
#else
		msg->msg_name = (void *)&dev->address.type.sa;
		msg->msg_namelen = sizeof(dev->address.type);
#endif
#ifdef ISC_NET_RECVOVERFLOW
		/* If needed, steal one iovec for overflow detection. */
		maxiov--;
#endif
	} else { /* TCP */
		msg->msg_name = NULL;
		msg->msg_namelen = 0;
		dev->address = sock->peer_address;
	}

	buffer = ISC_LIST_HEAD(dev->bufferlist);
	read_count = 0;

	/*
	 * Single buffer I/O?  Skip what we've done so far in this region.
	 */
	if (buffer == NULL) {
		read_count = dev->region.length - dev->n;
		iov[0].iov_base = (void *)(dev->region.base + dev->n);
		iov[0].iov_len = read_count;
		iovcount = 1;

		goto config;
	}

	/*
	 * Multibuffer I/O.
	 * Skip empty buffers.
	 */
	while (buffer != NULL) {
		REQUIRE(ISC_BUFFER_VALID(buffer));
		if (isc_buffer_availablelength(buffer) != 0)
			break;
		buffer = ISC_LIST_NEXT(buffer, link);
	}

	iovcount = 0;
	while (buffer != NULL) {
		INSIST(iovcount < MAXSCATTERGATHER_RECV);

		isc_buffer_availableregion(buffer, &available);

		if (available.length > 0) {
			iov[iovcount].iov_base = (void *)(available.base);
			iov[iovcount].iov_len = available.length;
			read_count += available.length;
			iovcount++;
		}
		buffer = ISC_LIST_NEXT(buffer, link);
	}

 config:

	/*
	 * If needed, set up to receive that one extra byte.  Note that
	 * we know there is at least one iov left, since we stole it
	 * at the top of this function.
	 */
#ifdef ISC_NET_RECVOVERFLOW
	if (sock->type == isc_sockettype_udp) {
		iov[iovcount].iov_base = (void *)(&sock->overflow);
		iov[iovcount].iov_len = 1;
		iovcount++;
	}
#endif

	msg->msg_iov = iov;
	msg->msg_iovlen = iovcount;

#ifdef ISC_NET_BSD44MSGHDR
	msg->msg_control = NULL;
	msg->msg_controllen = 0;
	msg->msg_flags = 0;
#if defined(USE_CMSG)
	if (sock->type == isc_sockettype_udp) {
		msg->msg_control = sock->recvcmsgbuf;
		msg->msg_controllen = sock->recvcmsgbuflen;
	}
#endif /* USE_CMSG */
#else /* ISC_NET_BSD44MSGHDR */
	msg->msg_accrights = NULL;
	msg->msg_accrightslen = 0;
#endif /* ISC_NET_BSD44MSGHDR */

	if (read_countp != NULL)
		*read_countp = read_count;
}
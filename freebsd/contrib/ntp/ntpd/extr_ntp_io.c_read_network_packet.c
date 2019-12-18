#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
struct recvbuf {int recv_length; int /*<<< orphan*/  receiver; int /*<<< orphan*/  recv_time; int /*<<< orphan*/  fd; struct interface* dstadr; TYPE_1__ recv_srcadr; int /*<<< orphan*/  recv_space; } ;
struct msghdr {int msg_namelen; int msg_iovlen; int msg_controllen; scalar_t__ msg_flags; void* msg_control; struct iovec* msg_iov; TYPE_1__* msg_name; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct interface {scalar_t__ family; int /*<<< orphan*/  received; TYPE_1__ sin; scalar_t__ ignore_packets; } ;
typedef  TYPE_1__ sockaddr_u ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  control ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  int GETSOCKNAME_SOCKLEN_TYPE ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int CMSG_BUFSIZE ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ ) ; 
 scalar_t__ ISREFCLOCKADR (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PSOCK_ADDR6 (TYPE_1__*) ; 
 int RX_BUFF_SIZE ; 
 int /*<<< orphan*/  add_full_recv_buffer (struct recvbuf*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fetch_timestamp (struct recvbuf*,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_recvbuffs () ; 
 int /*<<< orphan*/  freerecvbuf (struct recvbuf*) ; 
 struct recvbuf* get_free_recv_buffer () ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packets_dropped ; 
 int /*<<< orphan*/  packets_ignored ; 
 int /*<<< orphan*/  packets_received ; 
 int /*<<< orphan*/  receive ; 
 void* recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoa (TYPE_1__*) ; 

__attribute__((used)) static inline int
read_network_packet(
	SOCKET			fd,
	struct interface *	itf,
	l_fp			ts
	)
{
	GETSOCKNAME_SOCKLEN_TYPE fromlen;
	int buflen;
	register struct recvbuf *rb;
#ifdef HAVE_PACKET_TIMESTAMP
	struct msghdr msghdr;
	struct iovec iovec;
	char control[CMSG_BUFSIZE];
#endif

	/*
	 * Get a buffer and read the frame.  If we
	 * haven't got a buffer, or this is received
	 * on a disallowed socket, just dump the
	 * packet.
	 */

	rb = get_free_recv_buffer();
	if (NULL == rb || itf->ignore_packets) {
		char buf[RX_BUFF_SIZE];
		sockaddr_u from;

		if (rb != NULL)
			freerecvbuf(rb);

		fromlen = sizeof(from);
		buflen = recvfrom(fd, buf, sizeof(buf), 0,
				  &from.sa, &fromlen);
		DPRINTF(4, ("%s on (%lu) fd=%d from %s\n",
			(itf->ignore_packets)
			    ? "ignore"
			    : "drop",
			free_recvbuffs(), fd, stoa(&from)));
		if (itf->ignore_packets)
			packets_ignored++;
		else
			packets_dropped++;
		return (buflen);
	}

	fromlen = sizeof(rb->recv_srcadr);

#ifndef HAVE_PACKET_TIMESTAMP
	rb->recv_length = recvfrom(fd, (char *)&rb->recv_space,
				   sizeof(rb->recv_space), 0,
				   &rb->recv_srcadr.sa, &fromlen);
#else
	iovec.iov_base        = &rb->recv_space;
	iovec.iov_len         = sizeof(rb->recv_space);
	msghdr.msg_name       = &rb->recv_srcadr;
	msghdr.msg_namelen    = fromlen;
	msghdr.msg_iov        = &iovec;
	msghdr.msg_iovlen     = 1;
	msghdr.msg_control    = (void *)&control;
	msghdr.msg_controllen = sizeof(control);
	msghdr.msg_flags      = 0;
	rb->recv_length       = recvmsg(fd, &msghdr, 0);
#endif

	buflen = rb->recv_length;

	if (buflen == 0 || (buflen == -1 &&
	    (EWOULDBLOCK == errno
#ifdef EAGAIN
	     || EAGAIN == errno
#endif
	     ))) {
		freerecvbuf(rb);
		return (buflen);
	} else if (buflen < 0) {
		msyslog(LOG_ERR, "recvfrom(%s) fd=%d: %m",
			stoa(&rb->recv_srcadr), fd);
		DPRINTF(5, ("read_network_packet: fd=%d dropped (bad recvfrom)\n",
			    fd));
		freerecvbuf(rb);
		return (buflen);
	}

	DPRINTF(3, ("read_network_packet: fd=%d length %d from %s\n",
		    fd, buflen, stoa(&rb->recv_srcadr)));

#ifdef ENABLE_BUG3020_FIX
	if (ISREFCLOCKADR(&rb->recv_srcadr)) {
		msyslog(LOG_ERR, "recvfrom(%s) fd=%d: refclock srcadr on a network interface!",
			stoa(&rb->recv_srcadr), fd);
		DPRINTF(1, ("read_network_packet: fd=%d dropped (refclock srcadr))\n",
			    fd));
		packets_dropped++;
		freerecvbuf(rb);
		return (buflen);
	}
#endif

	/*
	** Bug 2672: Some OSes (MacOSX and Linux) don't block spoofed ::1
	*/

	if (AF_INET6 == itf->family) {
		DPRINTF(2, ("Got an IPv6 packet, from <%s> (%d) to <%s> (%d)\n",
			stoa(&rb->recv_srcadr),
			IN6_IS_ADDR_LOOPBACK(PSOCK_ADDR6(&rb->recv_srcadr)),
			stoa(&itf->sin),
			!IN6_IS_ADDR_LOOPBACK(PSOCK_ADDR6(&itf->sin))
			));

		if (   IN6_IS_ADDR_LOOPBACK(PSOCK_ADDR6(&rb->recv_srcadr))
		    && !IN6_IS_ADDR_LOOPBACK(PSOCK_ADDR6(&itf->sin))
		   ) {
			packets_dropped++;
			DPRINTF(2, ("DROPPING that packet\n"));
			freerecvbuf(rb);
			return buflen;
		}
		DPRINTF(2, ("processing that packet\n"));
	}

	/*
	 * Got one.  Mark how and when it got here,
	 * put it on the full list and do bookkeeping.
	 */
	rb->dstadr = itf;
	rb->fd = fd;
#ifdef HAVE_PACKET_TIMESTAMP
	/* pick up a network time stamp if possible */
	ts = fetch_timestamp(rb, &msghdr, ts);
#endif
	rb->recv_time = ts;
	rb->receiver = receive;

	add_full_recv_buffer(rb);

	itf->received++;
	packets_received++;
	return (buflen);
}
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
struct msghdr {int msg_iovlen; int msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 size_t INT_MAX ; 
 int MSG_TRUNC ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_DEBUG_MESSAGE (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 int recv (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_geterror (char*,char*,int) ; 

int sock_recv_dgram(SOCKET sock, void *buffer, size_t size,
    char *errbuf, int errbuflen)
{
	ssize_t nread;
#ifndef _WIN32
	struct msghdr message;
	struct iovec iov;
#endif

	if (size == 0)
	{
		SOCK_DEBUG_MESSAGE("I have been requested to read zero bytes");
		return 0;
	}
	if (size > INT_MAX)
	{
		if (errbuf)
		{
			pcap_snprintf(errbuf, errbuflen,
			    "Can't read more than %u bytes with sock_recv_dgram",
			    INT_MAX);
		}
		return -1;
	}

	/*
	 * This should be a datagram socket, so we should get the
	 * entire datagram in one recv() or recvmsg() call, and
	 * don't need to loop.
	 */
#ifdef _WIN32
	nread = recv(sock, buffer, size, 0);
	if (nread == SOCKET_ERROR)
	{
		/*
		 * To quote the MSDN documentation for recv(),
		 * "If the datagram or message is larger than
		 * the buffer specified, the buffer is filled
		 * with the first part of the datagram, and recv
		 * generates the error WSAEMSGSIZE. For unreliable
		 * protocols (for example, UDP) the excess data is
		 * lost..."
		 *
		 * So if the message is bigger than the buffer
		 * supplied to us, the excess data is discarded,
		 * and we'll report an error.
		 */
		sock_geterror("recv(): ", errbuf, errbuflen);
		return -1;
	}
#else /* _WIN32 */
	/*
	 * The Single UNIX Specification says that a recv() on
	 * a socket for a message-oriented protocol will discard
	 * the excess data.  It does *not* indicate that the
	 * receive will fail with, for example, EMSGSIZE.
	 *
	 * Therefore, we use recvmsg(), which appears to be
	 * the only way to get a "message truncated" indication
	 * when receiving a message for a message-oriented
	 * protocol.
	 */
	message.msg_name = NULL;	/* we don't care who it's from */
	message.msg_namelen = 0;
	iov.iov_base = buffer;
	iov.iov_len = size;
	message.msg_iov = &iov;
	message.msg_iovlen = 1;
#ifdef HAVE_STRUCT_MSGHDR_MSG_CONTROL
	message.msg_control = NULL;	/* we don't care about control information */
	message.msg_controllen = 0;
#endif
#ifdef HAVE_STRUCT_MSGHDR_MSG_FLAGS
	message.msg_flags = 0;
#endif
	nread = recvmsg(sock, &message, 0);
	if (nread == -1)
	{
		if (errno == EINTR)
			return -3;
		sock_geterror("recv(): ", errbuf, errbuflen);
		return -1;
	}
#ifdef HAVE_STRUCT_MSGHDR_MSG_FLAGS
	/*
	 * XXX - Solaris supports this, but only if you ask for the
	 * X/Open version of recvmsg(); should we use that, or will
	 * that cause other problems?
	 */
	if (message.msg_flags & MSG_TRUNC)
	{
		/*
		 * Message was bigger than the specified buffer size.
		 *
		 * Report this as an error, as the Microsoft documentation
		 * implies we'd do in a similar case on Windows.
		 */
		pcap_snprintf(errbuf, errbuflen, "recv(): Message too long");
		return -1;
	}
#endif /* HAVE_STRUCT_MSGHDR_MSG_FLAGS */
#endif /* _WIN32 */

	/*
	 * The size we're reading fits in an int, so the return value
	 * will fit in an int.
	 */
	return (int)nread;
}
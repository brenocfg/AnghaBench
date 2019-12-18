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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int ECONNRESET ; 
 int EPIPE ; 
 int GetLastError () ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int WSAECONNABORTED ; 
 int WSAECONNRESET ; 
 int errno ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,size_t) ; 
 int send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_fmterror (char*,int,char*,int) ; 

int sock_send(SOCKET sock, const char *buffer, size_t size,
    char *errbuf, int errbuflen)
{
	int remaining;
	ssize_t nsent;

	if (size > INT_MAX)
	{
		if (errbuf)
		{
			pcap_snprintf(errbuf, errbuflen,
			    "Can't send more than %u bytes with sock_recv",
			    INT_MAX);
		}
		return -1;
	}
	remaining = (int)size;

	do {
#ifdef MSG_NOSIGNAL
		/*
		 * Send with MSG_NOSIGNAL, so that we don't get SIGPIPE
		 * on errors on stream-oriented sockets when the other
		 * end breaks the connection.
		 * The EPIPE error is still returned.
		 */
		nsent = send(sock, buffer, remaining, MSG_NOSIGNAL);
#else
		nsent = send(sock, buffer, remaining, 0);
#endif

		if (nsent == -1)
		{
			/*
			 * If the client closed the connection out from
			 * under us, there's no need to log that as an
			 * error.
			 */
			int errcode;

#ifdef _WIN32
			errcode = GetLastError();
			if (errcode == WSAECONNRESET ||
			    errcode == WSAECONNABORTED)
			{
				/*
				 * WSAECONNABORTED appears to be the error
				 * returned in Winsock when you try to send
				 * on a connection where the peer has closed
				 * the receive side.
				 */
				return -2;
			}
			sock_fmterror("send(): ", errcode, errbuf, errbuflen);
#else
			errcode = errno;
			if (errcode == ECONNRESET || errcode == EPIPE)
			{
				/*
				 * EPIPE is what's returned on UN*X when
				 * you try to send on a connection when
				 * the peer has closed the receive side.
				 */
				return -2;
			}
			sock_fmterror("send(): ", errcode, errbuf, errbuflen);
#endif
			return -1;
		}

		remaining -= nsent;
		buffer += nsent;
	} while (remaining != 0);

	return 0;
}
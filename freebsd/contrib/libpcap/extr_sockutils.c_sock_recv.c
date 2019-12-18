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
 scalar_t__ EINTR ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  SOCK_DEBUG_MESSAGE (char*) ; 
 int SOCK_EOF_IS_ERROR ; 
 int SOCK_RECEIVEALL_YES ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_geterror (char*,char*,int) ; 

int sock_recv(SOCKET sock, void *buffer, size_t size, int flags,
    char *errbuf, int errbuflen)
{
	char *bufp = buffer;
	int remaining;
	ssize_t nread;

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
			    "Can't read more than %u bytes with sock_recv",
			    INT_MAX);
		}
		return -1;
	}

	bufp = (char *) buffer;
	remaining = (int) size;

	/*
	 * We don't use MSG_WAITALL because it's not supported in
	 * Win32.
	 */
	for (;;) {
		nread = recv(sock, bufp, remaining, 0);

		if (nread == -1)
		{
#ifndef _WIN32
			if (errno == EINTR)
				return -3;
#endif
			sock_geterror("recv(): ", errbuf, errbuflen);
			return -1;
		}

		if (nread == 0)
		{
			if ((flags & SOCK_EOF_IS_ERROR) ||
			    (remaining != (int) size))
			{
				/*
				 * Either we've already read some data,
				 * or we're always supposed to return
				 * an error on EOF.
				 */
				if (errbuf)
				{
					pcap_snprintf(errbuf, errbuflen,
					    "The other host terminated the connection.");
				}
				return -1;
			}
			else
				return 0;
		}

		/*
		 * Do we want to read the amount requested, or just return
		 * what we got?
		 */
		if (!(flags & SOCK_RECEIVEALL_YES))
		{
			/*
			 * Just return what we got.
			 */
			return (int) nread;
		}

		bufp += nread;
		remaining -= nread;

		if (remaining == 0)
			return (int) size;
	}
}
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
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_socktype; int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sock_geterror (char*,char*,int) ; 
 scalar_t__ sock_ismcastaddr (int /*<<< orphan*/ ) ; 

int sock_initaddress(const char *host, const char *port,
    struct addrinfo *hints, struct addrinfo **addrinfo, char *errbuf, int errbuflen)
{
	int retval;

	retval = getaddrinfo(host, port, hints, addrinfo);
	if (retval != 0)
	{
		/*
		 * if the getaddrinfo() fails, you have to use gai_strerror(), instead of using the standard
		 * error routines (errno) in UNIX; Winsock suggests using the GetLastError() instead.
		 */
		if (errbuf)
		{
#ifdef _WIN32
			sock_geterror("getaddrinfo(): ", errbuf, errbuflen);
#else
			pcap_snprintf(errbuf, errbuflen, "getaddrinfo() %s", gai_strerror(retval));
#endif
		}
		return -1;
	}
	/*
	 * \warning SOCKET: I should check all the accept() in order to bind to all addresses in case
	 * addrinfo has more han one pointers
	 */

	/*
	 * This software only supports PF_INET and PF_INET6.
	 *
	 * XXX - should we just check that at least *one* address is
	 * either PF_INET or PF_INET6, and, when using the list,
	 * ignore all addresses that are neither?  (What, no IPX
	 * support? :-))
	 */
	if (((*addrinfo)->ai_family != PF_INET) &&
	    ((*addrinfo)->ai_family != PF_INET6))
	{
		if (errbuf)
			pcap_snprintf(errbuf, errbuflen, "getaddrinfo(): socket type not supported");
		freeaddrinfo(*addrinfo);
		*addrinfo = NULL;
		return -1;
	}

	/*
	 * You can't do multicast (or broadcast) TCP.
	 */
	if (((*addrinfo)->ai_socktype == SOCK_STREAM) &&
	    (sock_ismcastaddr((*addrinfo)->ai_addr) == 0))
	{
		if (errbuf)
			pcap_snprintf(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
		freeaddrinfo(*addrinfo);
		*addrinfo = NULL;
		return -1;
	}

	return 0;
}
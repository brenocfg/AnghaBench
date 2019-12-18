#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct addrinfo {TYPE_1__* ai_addr; struct addrinfo* ai_next; void* ai_protocol; int /*<<< orphan*/  ai_socktype; void* ai_family; } ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EAI_NONAME ; 
 void* IPPROTO_TCP ; 
 void* IPPROTO_UDP ; 
 void* PF_UNSPEC ; 
 int PROTO_UNDEF ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

int
pcap_nametoport(const char *name, int *port, int *proto)
{
	struct addrinfo hints, *res, *ai;
	int error;
	struct sockaddr_in *in4;
#ifdef INET6
	struct sockaddr_in6 *in6;
#endif
	int tcp_port = -1;
	int udp_port = -1;

	/*
	 * We check for both TCP and UDP in case there are
	 * ambiguous entries.
	 */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	error = getaddrinfo(NULL, name, &hints, &res);
	if (error != 0) {
		if (error != EAI_NONAME) {
			/*
			 * This is a real error, not just "there's
			 * no such service name".
			 * XXX - this doesn't return an error string.
			 */
			return 0;
		}
	} else {
		/*
		 * OK, we found it.  Did it find anything?
		 */
		for (ai = res; ai != NULL; ai = ai->ai_next) {
			/*
			 * Does it have an address?
			 */
			if (ai->ai_addr != NULL) {
				/*
				 * Yes.  Get a port number; we're done.
				 */
				if (ai->ai_addr->sa_family == AF_INET) {
					in4 = (struct sockaddr_in *)ai->ai_addr;
					tcp_port = ntohs(in4->sin_port);
					break;
				}
#ifdef INET6
				if (ai->ai_addr->sa_family == AF_INET6) {
					in6 = (struct sockaddr_in6 *)ai->ai_addr;
					tcp_port = ntohs(in6->sin6_port);
					break;
				}
#endif
			}
		}
		freeaddrinfo(res);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	error = getaddrinfo(NULL, name, &hints, &res);
	if (error != 0) {
		if (error != EAI_NONAME) {
			/*
			 * This is a real error, not just "there's
			 * no such service name".
			 * XXX - this doesn't return an error string.
			 */
			return 0;
		}
	} else {
		/*
		 * OK, we found it.  Did it find anything?
		 */
		for (ai = res; ai != NULL; ai = ai->ai_next) {
			/*
			 * Does it have an address?
			 */
			if (ai->ai_addr != NULL) {
				/*
				 * Yes.  Get a port number; we're done.
				 */
				if (ai->ai_addr->sa_family == AF_INET) {
					in4 = (struct sockaddr_in *)ai->ai_addr;
					udp_port = ntohs(in4->sin_port);
					break;
				}
#ifdef INET6
				if (ai->ai_addr->sa_family == AF_INET6) {
					in6 = (struct sockaddr_in6 *)ai->ai_addr;
					udp_port = ntohs(in6->sin6_port);
					break;
				}
#endif
			}
		}
		freeaddrinfo(res);
	}

	/*
	 * We need to check /etc/services for ambiguous entries.
	 * If we find an ambiguous entry, and it has the
	 * same port number, change the proto to PROTO_UNDEF
	 * so both TCP and UDP will be checked.
	 */
	if (tcp_port >= 0) {
		*port = tcp_port;
		*proto = IPPROTO_TCP;
		if (udp_port >= 0) {
			if (udp_port == tcp_port)
				*proto = PROTO_UNDEF;
#ifdef notdef
			else
				/* Can't handle ambiguous names that refer
				   to different port numbers. */
				warning("ambiguous port %s in /etc/services",
					name);
#endif
		}
		return 1;
	}
	if (udp_port >= 0) {
		*port = udp_port;
		*proto = IPPROTO_UDP;
		return 1;
	}
#if defined(ultrix) || defined(__osf__)
	/* Special hack in case NFS isn't in /etc/services */
	if (strcmp(name, "nfs") == 0) {
		*port = 2049;
		*proto = PROTO_UNDEF;
		return 1;
	}
#endif
	return 0;
}
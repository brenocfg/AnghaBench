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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; void* sin6_port; void* sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; void* sin_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; void* sin6_port; void* sin6_family; int /*<<< orphan*/  sin_addr; void* sin_port; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin_out ;
typedef  int /*<<< orphan*/  sin6_out ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int ev_socklen_t ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ evutil_check_ifaddrs () ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  evutil_found_ifaddr (struct sockaddr*) ; 
 int evutil_inet_pton (void*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 int have_checked_interfaces ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evutil_check_interfaces(void)
{
	evutil_socket_t fd = -1;
	struct sockaddr_in sin, sin_out;
	struct sockaddr_in6 sin6, sin6_out;
	ev_socklen_t sin_out_len = sizeof(sin_out);
	ev_socklen_t sin6_out_len = sizeof(sin6_out);
	int r;
	if (have_checked_interfaces)
		return 0;

	/* From this point on we have done the ipv4/ipv6 interface check */
	have_checked_interfaces = 1;

	if (evutil_check_ifaddrs() == 0) {
		/* Use a nice sane interface, if this system has one. */
		return 0;
	}

	/* Ugh. There was no nice sane interface.  So to check whether we have
	 * an interface open for a given protocol, will try to make a UDP
	 * 'connection' to a remote host on the internet.  We don't actually
	 * use it, so the address doesn't matter, but we want to pick one that
	 * keep us from using a host- or link-local interface. */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(53);
	r = evutil_inet_pton(AF_INET, "18.244.0.188", &sin.sin_addr);
	EVUTIL_ASSERT(r);

	memset(&sin6, 0, sizeof(sin6));
	sin6.sin6_family = AF_INET6;
	sin6.sin6_port = htons(53);
	r = evutil_inet_pton(AF_INET6, "2001:4860:b002::68", &sin6.sin6_addr);
	EVUTIL_ASSERT(r);

	memset(&sin_out, 0, sizeof(sin_out));
	memset(&sin6_out, 0, sizeof(sin6_out));

	/* XXX some errnos mean 'no address'; some mean 'not enough sockets'. */
	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) >= 0 &&
	    connect(fd, (struct sockaddr*)&sin, sizeof(sin)) == 0 &&
	    getsockname(fd, (struct sockaddr*)&sin_out, &sin_out_len) == 0) {
		/* We might have an IPv4 interface. */
		evutil_found_ifaddr((struct sockaddr*) &sin_out);
	}
	if (fd >= 0)
		evutil_closesocket(fd);

	if ((fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) >= 0 &&
	    connect(fd, (struct sockaddr*)&sin6, sizeof(sin6)) == 0 &&
	    getsockname(fd, (struct sockaddr*)&sin6_out, &sin6_out_len) == 0) {
		/* We might have an IPv6 interface. */
		evutil_found_ifaddr((struct sockaddr*) &sin6_out);
	}

	if (fd >= 0)
		evutil_closesocket(fd);

	return 0;
}
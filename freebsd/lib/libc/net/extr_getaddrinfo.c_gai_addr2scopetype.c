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
typedef  int u_char ;
struct TYPE_5__ {int* s6_addr; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (TYPE_1__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LOOPBACK (TYPE_1__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MULTICAST (TYPE_1__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_SITELOCAL (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int
gai_addr2scopetype(struct sockaddr *sa)
{
#ifdef INET6
	struct sockaddr_in6 *sa6;
#endif
	struct sockaddr_in *sa4;

	switch(sa->sa_family) {
#ifdef INET6
	case AF_INET6:
		sa6 = (struct sockaddr_in6 *)sa;
		if (IN6_IS_ADDR_MULTICAST(&sa6->sin6_addr)) {
			/* just use the scope field of the multicast address */
			return(sa6->sin6_addr.s6_addr[2] & 0x0f);
		}
		/*
		 * Unicast addresses: map scope type to corresponding scope
		 * value defined for multcast addresses.
		 * XXX: hardcoded scope type values are bad...
		 */
		if (IN6_IS_ADDR_LOOPBACK(&sa6->sin6_addr))
			return(1); /* node local scope */
		if (IN6_IS_ADDR_LINKLOCAL(&sa6->sin6_addr))
			return(2); /* link-local scope */
		if (IN6_IS_ADDR_SITELOCAL(&sa6->sin6_addr))
			return(5); /* site-local scope */
		return(14);	/* global scope */
		break;
#endif
	case AF_INET:
		/*
		 * IPv4 pseudo scoping according to RFC 3484.
		 */
		sa4 = (struct sockaddr_in *)sa;
		/* IPv4 autoconfiguration addresses have link-local scope. */
		if (((u_char *)&sa4->sin_addr)[0] == 169 &&
		    ((u_char *)&sa4->sin_addr)[1] == 254)
			return(2);
		/* Private addresses have site-local scope. */
		if (((u_char *)&sa4->sin_addr)[0] == 10 ||
		    (((u_char *)&sa4->sin_addr)[0] == 172 &&
		     (((u_char *)&sa4->sin_addr)[1] & 0xf0) == 16) ||
		    (((u_char *)&sa4->sin_addr)[0] == 192 &&
		     ((u_char *)&sa4->sin_addr)[1] == 168))
			return(14);	/* XXX: It should be 5 unless NAT */
		/* Loopback addresses have link-local scope. */
		if (((u_char *)&sa4->sin_addr)[0] == 127)
			return(2);
		return(14);
		break;
	default:
		errno = EAFNOSUPPORT; /* is this a good error? */
		return(-1);
	}
}
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
typedef  int /*<<< orphan*/  u_int ;
struct interface {int /*<<< orphan*/  sin; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  off6 ;
typedef  int /*<<< orphan*/  off ;
typedef  int /*<<< orphan*/  TYPEOF_IP_MULTICAST_LOOP ;

/* Variables and functions */
 int AF (int /*<<< orphan*/ *) ; 
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_MULTICAST_LOOP ; 
 int /*<<< orphan*/  IP_MULTICAST_LOOP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

void
enable_multicast_if(
	struct interface *	iface,
	sockaddr_u *		maddr
	)
{
#ifdef MCAST
#ifdef IP_MULTICAST_LOOP
	TYPEOF_IP_MULTICAST_LOOP off = 0;
#endif
#if defined(INCLUDE_IPV6_MULTICAST_SUPPORT) && defined(IPV6_MULTICAST_LOOP)
	u_int off6 = 0;
#endif

	REQUIRE(AF(maddr) == AF(&iface->sin));

	switch (AF(&iface->sin)) {

	case AF_INET:
#ifdef IP_MULTICAST_LOOP
		/*
		 * Don't send back to itself, but allow failure to set
		 */
		if (setsockopt(iface->fd, IPPROTO_IP,
			       IP_MULTICAST_LOOP,
			       (void *)&off,
			       sizeof(off))) {

			msyslog(LOG_ERR,
				"setsockopt IP_MULTICAST_LOOP failed: %m on socket %d, addr %s for multicast address %s",
				iface->fd, stoa(&iface->sin),
				stoa(maddr));
		}
#endif
		break;

	case AF_INET6:
#ifdef INCLUDE_IPV6_MULTICAST_SUPPORT
#ifdef IPV6_MULTICAST_LOOP
		/*
		 * Don't send back to itself, but allow failure to set
		 */
		if (setsockopt(iface->fd, IPPROTO_IPV6,
			       IPV6_MULTICAST_LOOP,
			       (void *) &off6, sizeof(off6))) {

			msyslog(LOG_ERR,
				"setsockopt IPV6_MULTICAST_LOOP failed: %m on socket %d, addr %s for multicast address %s",
				iface->fd, stoa(&iface->sin),
				stoa(maddr));
		}
#endif
		break;
#else
		return;
#endif	/* INCLUDE_IPV6_MULTICAST_SUPPORT */
	}
	return;
#endif
}
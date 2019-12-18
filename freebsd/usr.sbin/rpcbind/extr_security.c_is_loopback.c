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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct netbuf {scalar_t__ buf; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 int /*<<< orphan*/  IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  IPPORT_RESERVED ; 
 int /*<<< orphan*/  IPV6PORT_RESERVED ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oldstyle_local ; 

int
is_loopback(struct netbuf *nbuf)
{
	struct sockaddr *addr = (struct sockaddr *)nbuf->buf;
	struct sockaddr_in *sin;
#ifdef INET6
	struct sockaddr_in6 *sin6;
#endif

	switch (addr->sa_family) {
	case AF_INET:
		if (!oldstyle_local)
			return 0;
		sin = (struct sockaddr_in *)addr;
        	return ((sin->sin_addr.s_addr == htonl(INADDR_LOOPBACK)) &&
		    (ntohs(sin->sin_port) < IPPORT_RESERVED));
#ifdef INET6
	case AF_INET6:
		if (!oldstyle_local)
			return 0;
		sin6 = (struct sockaddr_in6 *)addr;
		return (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr) &&
		    (ntohs(sin6->sin6_port) < IPV6PORT_RESERVED));
#endif
	case AF_LOCAL:
		return 1;
	default:
		break;
	}
	
	return 0;
}
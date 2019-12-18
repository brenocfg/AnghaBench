#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  scalar_t__ ev_uint32_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ EVUTIL_V4ADDR_IS_CLASSD (scalar_t__) ; 
 scalar_t__ EVUTIL_V4ADDR_IS_LOCALHOST (scalar_t__) ; 
 int /*<<< orphan*/  event_debug (char*) ; 
 int had_ipv4_address ; 
 int had_ipv6_address ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,char const*,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evutil_found_ifaddr(const struct sockaddr *sa)
{
	const char ZEROES[] = "\x00\x00\x00\x00\x00\x00\x00\x00"
	    "\x00\x00\x00\x00\x00\x00\x00\x00";

	if (sa->sa_family == AF_INET) {
		const struct sockaddr_in *sin = (struct sockaddr_in *)sa;
		ev_uint32_t addr = ntohl(sin->sin_addr.s_addr);
		if (addr == 0 ||
		    EVUTIL_V4ADDR_IS_LOCALHOST(addr) ||
		    EVUTIL_V4ADDR_IS_CLASSD(addr)) {
			/* Not actually a usable external address. */
		} else {
			event_debug(("Detected an IPv4 interface"));
			had_ipv4_address = 1;
		}
	} else if (sa->sa_family == AF_INET6) {
		const struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
		const unsigned char *addr =
		    (unsigned char*)sin6->sin6_addr.s6_addr;
		if (!memcmp(addr, ZEROES, 8) ||
		    ((addr[0] & 0xfe) == 0xfc) ||
		    (addr[0] == 0xfe && (addr[1] & 0xc0) == 0x80) ||
		    (addr[0] == 0xfe && (addr[1] & 0xc0) == 0xc0) ||
		    (addr[0] == 0xff)) {
			/* This is a reserved, ipv4compat, ipv4map, loopback,
			 * link-local, multicast, or unspecified address. */
		} else {
			event_debug(("Detected an IPv6 interface"));
			had_ipv6_address = 1;
		}
	}
}
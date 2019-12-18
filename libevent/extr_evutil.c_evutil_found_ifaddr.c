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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  event_debug (char*) ; 
 int /*<<< orphan*/  evutil_v4addr_is_local_ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_v6addr_is_local_ (int /*<<< orphan*/ *) ; 
 int had_ipv4_address ; 
 int had_ipv6_address ; 

__attribute__((used)) static void
evutil_found_ifaddr(const struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		const struct sockaddr_in *sin = (struct sockaddr_in *)sa;
		if (!evutil_v4addr_is_local_(&sin->sin_addr)) {
			event_debug(("Detected an IPv4 interface"));
			had_ipv4_address = 1;
		}
	} else if (sa->sa_family == AF_INET6) {
		const struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
		if (!evutil_v6addr_is_local_(&sin6->sin6_addr)) {
			event_debug(("Detected an IPv6 interface"));
			had_ipv6_address = 1;
		}
	}
}
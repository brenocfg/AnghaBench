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
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int
evutil_sockaddr_is_loopback_(const struct sockaddr *addr)
{
	static const char LOOPBACK_S6[16] =
	    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1";
	if (addr->sa_family == AF_INET) {
		struct sockaddr_in *sin = (struct sockaddr_in *)addr;
		return (ntohl(sin->sin_addr.s_addr) & 0xff000000) == 0x7f000000;
	} else if (addr->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)addr;
		return !memcmp(sin6->sin6_addr.s6_addr, LOOPBACK_S6, 16);
	}
	return 0;
}
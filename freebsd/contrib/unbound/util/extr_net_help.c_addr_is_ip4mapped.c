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
typedef  int uint8_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 

int 
addr_is_ip4mapped(struct sockaddr_storage* addr, socklen_t addrlen)
{
	/* prefix for ipv4 into ipv6 mapping is ::ffff:x.x.x.x */
	const uint8_t map_prefix[16] = 
		{0,0,0,0,  0,0,0,0, 0,0,0xff,0xff, 0,0,0,0};
	uint8_t* s;
	if(!addr_is_ip6(addr, addrlen))
		return 0;
	/* s is 16 octet ipv6 address string */
	s = (uint8_t*)&((struct sockaddr_in6*)addr)->sin6_addr;
	return (memcmp(s, map_prefix, 12) == 0);
}
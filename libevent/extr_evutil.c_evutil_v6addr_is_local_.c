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
struct in6_addr {scalar_t__ s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char const*,char const*,int) ; 

int
evutil_v6addr_is_local_(const struct in6_addr *in)
{
	static const char ZEROES[] =
		"\x00\x00\x00\x00\x00\x00\x00\x00"
		"\x00\x00\x00\x00\x00\x00\x00\x00";

	const unsigned char *addr = (const unsigned char *)in->s6_addr;
	return !memcmp(addr, ZEROES, 8) ||
		((addr[0] & 0xfe) == 0xfc) ||
		(addr[0] == 0xfe && (addr[1] & 0xc0) == 0x80) ||
		(addr[0] == 0xfe && (addr[1] & 0xc0) == 0xc0) ||
		(addr[0] == 0xff);
}
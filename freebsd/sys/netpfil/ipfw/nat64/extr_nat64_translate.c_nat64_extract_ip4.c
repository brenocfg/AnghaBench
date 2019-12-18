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
struct in6_addr {int* s6_addr32; int /*<<< orphan*/ * s6_addr8; } ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*,...) ; 
 int DP_DROPS ; 
 int DP_GENERIC ; 
 int htonl (int) ; 
 scalar_t__ nat64_check_ip4 (int) ; 

in_addr_t
nat64_extract_ip4(const struct in6_addr *ip6, int plen)
{
	in_addr_t ia;

	/*
	 * According to RFC 6052 p2.2:
	 * IPv4-embedded IPv6 addresses are composed of a variable-length
	 * prefix, the embedded IPv4 address, and a variable length suffix.
	 * The suffix bits are reserved for future extensions and SHOULD
	 * be set to zero.
	 */
	switch (plen) {
	case 32:
		if (ip6->s6_addr32[3] != 0 || ip6->s6_addr32[2] != 0)
			goto badip6;
		break;
	case 40:
		if (ip6->s6_addr32[3] != 0 ||
		    (ip6->s6_addr32[2] & htonl(0xff00ffff)) != 0)
			goto badip6;
		break;
	case 48:
		if (ip6->s6_addr32[3] != 0 ||
		    (ip6->s6_addr32[2] & htonl(0xff0000ff)) != 0)
			goto badip6;
		break;
	case 56:
		if (ip6->s6_addr32[3] != 0 || ip6->s6_addr8[8] != 0)
			goto badip6;
		break;
	case 64:
		if (ip6->s6_addr8[8] != 0 ||
		    (ip6->s6_addr32[3] & htonl(0x00ffffff)) != 0)
			goto badip6;
	};
	switch (plen) {
	case 32:
	case 96:
		ia = ip6->s6_addr32[plen / 32];
		break;
	case 40:
	case 48:
	case 56:
#if BYTE_ORDER == BIG_ENDIAN
		ia = (ip6->s6_addr32[1] << (plen % 32)) |
		    (ip6->s6_addr32[2] >> (24 - plen % 32));
#elif BYTE_ORDER == LITTLE_ENDIAN
		ia = (ip6->s6_addr32[1] >> (plen % 32)) |
		    (ip6->s6_addr32[2] << (24 - plen % 32));
#endif
		break;
	case 64:
#if BYTE_ORDER == BIG_ENDIAN
		ia = (ip6->s6_addr32[2] << 8) | (ip6->s6_addr32[3] >> 24);
#elif BYTE_ORDER == LITTLE_ENDIAN
		ia = (ip6->s6_addr32[2] >> 8) | (ip6->s6_addr32[3] << 24);
#endif
		break;
	default:
		return (0);
	};
	if (nat64_check_ip4(ia) == 0)
		return (ia);

	DPRINTF(DP_GENERIC | DP_DROPS,
	    "invalid destination address: %08x", ia);
	return (0);
badip6:
	DPRINTF(DP_GENERIC | DP_DROPS, "invalid IPv4-embedded IPv6 address");
	return (0);
}
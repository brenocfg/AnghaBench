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
struct in6_addr {int* s6_addr32; scalar_t__* s6_addr8; } ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int) ; 

void
nat64_embed_ip4(struct in6_addr *ip6, int plen, in_addr_t ia)
{

	switch (plen) {
	case 32:
	case 96:
		ip6->s6_addr32[plen / 32] = ia;
		break;
	case 40:
	case 48:
	case 56:
		/*
		 * Preserve prefix bits.
		 * Since suffix bits should be zero and reserved for future
		 * use, we just overwrite the whole word, where they are.
		 */
		ip6->s6_addr32[1] &= 0xffffffff << (32 - plen % 32);
#if BYTE_ORDER == BIG_ENDIAN
		ip6->s6_addr32[1] |= ia >> (plen % 32);
		ip6->s6_addr32[2] = ia << (24 - plen % 32);
#elif BYTE_ORDER == LITTLE_ENDIAN
		ip6->s6_addr32[1] |= ia << (plen % 32);
		ip6->s6_addr32[2] = ia >> (24 - plen % 32);
#endif
		break;
	case 64:
#if BYTE_ORDER == BIG_ENDIAN
		ip6->s6_addr32[2] = ia >> 8;
		ip6->s6_addr32[3] = ia << 24;
#elif BYTE_ORDER == LITTLE_ENDIAN
		ip6->s6_addr32[2] = ia << 8;
		ip6->s6_addr32[3] = ia >> 24;
#endif
		break;
	default:
		panic("Wrong plen: %d", plen);
	};
	/*
	 * Bits 64 to 71 of the address are reserved for compatibility
	 * with the host identifier format defined in the IPv6 addressing
	 * architecture [RFC4291]. These bits MUST be set to zero.
	 */
	ip6->s6_addr8[8] = 0;
}
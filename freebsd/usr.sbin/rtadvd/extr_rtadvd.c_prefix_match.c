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
struct in6_addr {char* s6_addr; } ;

/* Variables and functions */
 scalar_t__ memcmp (void*,void*,int) ; 

int
prefix_match(struct in6_addr *p0, int plen0,
	struct in6_addr *p1, int plen1)
{
	int bytelen, bitlen;
	char bitmask;

	if (plen0 < plen1)
		return (0);

	bytelen = plen1 / 8;
	bitlen = plen1 % 8;
	bitmask = 0xff << (8 - bitlen);

	if (memcmp((void *)p0, (void *)p1, bytelen))
		return (0);

	if (bitlen == 0 ||
	    ((p0->s6_addr[bytelen] & bitmask) ==
	     (p1->s6_addr[bytelen] & bitmask))) {
		return (1);
	}

	return (0);
}
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
struct ip6_rthdr0 {int ip6r0_segleft; int ip6r0_len; } ;
struct ip6_rthdr {int ip6r_type; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  IPV6_RTHDR_TYPE_0 128 

int
inet6_rth_add(void *bp, const struct in6_addr *addr)
{
	struct ip6_rthdr *rth = (struct ip6_rthdr *)bp;
	struct ip6_rthdr0 *rth0;
	struct in6_addr *nextaddr;

	switch (rth->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
		rth0 = (struct ip6_rthdr0 *)rth;
		/* Don't exceed the number of stated segments */
		if (rth0->ip6r0_segleft == (rth0->ip6r0_len / 2))
			return (-1);
		nextaddr = (struct in6_addr *)(rth0 + 1) + rth0->ip6r0_segleft;
		*nextaddr = *addr;
		rth0->ip6r0_segleft++;
		break;
	default:
		return (-1);	/* type not supported */
	}

	return (0);
}
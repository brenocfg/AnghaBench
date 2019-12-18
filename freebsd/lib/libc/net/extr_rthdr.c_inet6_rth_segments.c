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
struct ip6_rthdr0 {int ip6r0_len; int ip6r0_segleft; } ;
struct ip6_rthdr {int ip6r_type; } ;

/* Variables and functions */
#define  IPV6_RTHDR_TYPE_0 128 

int
inet6_rth_segments(const void *bp)
{
	struct ip6_rthdr *rh = (struct ip6_rthdr *)bp;
	struct ip6_rthdr0 *rh0;
	int addrs;

	switch (rh->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
		rh0 = (struct ip6_rthdr0 *)bp;

		/*
		 * Validation for a type-0 routing header.
		 * Is this too strict?
		 */
		if ((rh0->ip6r0_len % 2) != 0 ||
		    (addrs = (rh0->ip6r0_len >> 1)) < rh0->ip6r0_segleft)
			return (-1);

		return (addrs);
	default:
		return (-1);	/* unknown type */
	}
}
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
struct ip6_rthdr0 {int ip6r0_len; } ;
struct ip6_rthdr {int ip6r_type; } ;
struct in6_addr {int dummy; } ;
struct cmsghdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr const*) ; 
#define  IPV6_RTHDR_TYPE_0 128 

int
inet6_rthdr_segments(const struct cmsghdr *cmsg)
{
	struct ip6_rthdr *rthdr;

	rthdr = (struct ip6_rthdr *)CMSG_DATA(cmsg);

	switch (rthdr->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
	{
		struct ip6_rthdr0 *rt0 = (struct ip6_rthdr0 *)rthdr;

		if (rt0->ip6r0_len % 2 || 46 < rt0->ip6r0_len)
			return (-1);

		return (rt0->ip6r0_len * 8) / sizeof(struct in6_addr);
	}

	default:
		return (-1);
	}
}
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
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
#define  IPV6_RTHDR_TYPE_0 128 

struct in6_addr *
inet6_rthdr_getaddr(struct cmsghdr *cmsg, int idx)
{
	struct ip6_rthdr *rthdr;

	rthdr = (struct ip6_rthdr *)CMSG_DATA(cmsg);

	switch (rthdr->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
	{
		struct ip6_rthdr0 *rt0 = (struct ip6_rthdr0 *)rthdr;
		int naddr;

		if (rt0->ip6r0_len % 2 || 46 < rt0->ip6r0_len)
			return NULL;
		naddr = (rt0->ip6r0_len * 8) / sizeof(struct in6_addr);
		if (idx <= 0 || naddr < idx)
			return NULL;
#ifdef COMPAT_RFC2292
		return (((struct in6_addr *)(rt0 + 1)) + idx - 1);
#else
		return (((struct in6_addr *)(rt0 + 1)) + idx);
#endif
	}

	default:
		return NULL;
	}
}
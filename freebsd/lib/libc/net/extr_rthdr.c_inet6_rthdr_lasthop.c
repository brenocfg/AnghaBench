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
struct ip6_rthdr0 {int ip6r0_segleft; int* ip6r0_slmap; } ;
struct ip6_rthdr {int ip6r_type; } ;
struct cmsghdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 unsigned int IPV6_RTHDR_LOOSE ; 
 unsigned int IPV6_RTHDR_STRICT ; 
#define  IPV6_RTHDR_TYPE_0 128 

int
inet6_rthdr_lasthop(struct cmsghdr *cmsg, unsigned int flags)
{
	struct ip6_rthdr *rthdr;

	rthdr = (struct ip6_rthdr *)CMSG_DATA(cmsg);

	switch (rthdr->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
	{
		struct ip6_rthdr0 *rt0 = (struct ip6_rthdr0 *)rthdr;
#ifdef COMPAT_RFC1883		/* XXX */
		if (flags != IPV6_RTHDR_LOOSE && flags != IPV6_RTHDR_STRICT)
			return (-1);
#endif /* COMPAT_RFC1883 */
		if (rt0->ip6r0_segleft > 23)
			return (-1);
#ifdef COMPAT_RFC1883		/* XXX */
		if (flags == IPV6_RTHDR_STRICT) {
			int c, b;
			c = rt0->ip6r0_segleft / 8;
			b = rt0->ip6r0_segleft % 8;
			rt0->ip6r0_slmap[c] |= (1 << (7 - b));
		}
#else
		if (flags != IPV6_RTHDR_LOOSE)
			return (-1);
#endif /* COMPAT_RFC1883 */
		break;
	}
	default:
		return (-1);
	}

	return (0);
}
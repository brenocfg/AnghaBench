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
typedef  int /*<<< orphan*/  u_int ;
struct ip6_rthdr0 {int ip6r0_segleft; int* ip6r0_slmap; int ip6r0_len; } ;
struct ip6_rthdr {int ip6r_type; } ;
struct in6_addr {int dummy; } ;
struct cmsghdr {int /*<<< orphan*/  cmsg_len; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int /*<<< orphan*/  IPV6_RTHDR_LOOSE ; 
 int /*<<< orphan*/  IPV6_RTHDR_STRICT ; 
#define  IPV6_RTHDR_TYPE_0 128 
 int /*<<< orphan*/  bcopy (struct in6_addr const*,int /*<<< orphan*/ ,int) ; 

int
inet6_rthdr_add(struct cmsghdr *cmsg, const struct in6_addr *addr, u_int flags)
{
	struct ip6_rthdr *rthdr;

	rthdr = (struct ip6_rthdr *)CMSG_DATA(cmsg);

	switch (rthdr->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
	{
		struct ip6_rthdr0 *rt0 = (struct ip6_rthdr0 *)rthdr;
		if (flags != IPV6_RTHDR_LOOSE && flags != IPV6_RTHDR_STRICT)
			return (-1);
		if (rt0->ip6r0_segleft == 23)
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
#endif 
		rt0->ip6r0_segleft++;
		bcopy(addr, (caddr_t)rt0 + ((rt0->ip6r0_len + 1) << 3),
		    sizeof(struct in6_addr));
		rt0->ip6r0_len += sizeof(struct in6_addr) >> 3;
		cmsg->cmsg_len = CMSG_LEN((rt0->ip6r0_len + 1) << 3);
		break;
	}
	default:
		return (-1);
	}

	return (0);
}
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
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  IPV6_RTHDR_TYPE_0 128 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 

int
inet6_rth_reverse(const void *in, void *out)
{
	struct ip6_rthdr *rth_in = (struct ip6_rthdr *)in;
	struct ip6_rthdr0 *rth0_in, *rth0_out;
	int i, segments;

	switch (rth_in->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
		rth0_in = (struct ip6_rthdr0 *)in;
		rth0_out = (struct ip6_rthdr0 *)out;

		/* parameter validation XXX too paranoid? */
		if (rth0_in->ip6r0_len % 2)
			return (-1);
		segments = rth0_in->ip6r0_len / 2;

		/* we can't use memcpy here, since in and out may overlap */
		memmove((void *)rth0_out, (void *)rth0_in,
			((rth0_in->ip6r0_len) + 1) << 3);
		rth0_out->ip6r0_segleft = segments;

		/* reverse the addresses */
		for (i = 0; i < segments / 2; i++) {
			struct in6_addr addr_tmp, *addr1, *addr2;

			addr1 = (struct in6_addr *)(rth0_out + 1) + i;
			addr2 = (struct in6_addr *)(rth0_out + 1) +
				(segments - i - 1);
			addr_tmp = *addr1;
			*addr1 = *addr2;
			*addr2 = addr_tmp;
		}

		break;
	default:
		return (-1);	/* type not supported */
	}

	return (0);
}
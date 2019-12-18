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
struct ip6_rthdr0 {int ip6r0_len; int ip6r0_type; int /*<<< orphan*/  ip6r0_reserved; int /*<<< orphan*/  ip6r0_segleft; } ;
struct ip6_rthdr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  IPV6_RTHDR_TYPE_0 128 
 int /*<<< orphan*/  inet6_rth_space (int const,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
inet6_rth_init(void *bp, socklen_t bp_len, int type, int segments)
{
	struct ip6_rthdr *rth = (struct ip6_rthdr *)bp;
	struct ip6_rthdr0 *rth0;

	switch (type) {
	case IPV6_RTHDR_TYPE_0:
		/* length validation */
		if (bp_len < inet6_rth_space(IPV6_RTHDR_TYPE_0, segments))
			return (NULL);
		/* segment validation */
		if ((segments < 0) || (segments > 127))
			return (NULL);

		memset(bp, 0, bp_len);
		rth0 = (struct ip6_rthdr0 *)rth;
		rth0->ip6r0_len = segments * 2;
		rth0->ip6r0_type = IPV6_RTHDR_TYPE_0;
		rth0->ip6r0_segleft = 0;
		rth0->ip6r0_reserved = 0;
		break;
	default:
		return (NULL);	/* type not supported */
	}

	return (bp);
}
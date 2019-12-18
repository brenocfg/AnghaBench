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
struct ip6_rthdr0 {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 size_t CMSG_SPACE (int) ; 
#define  IPV6_RTHDR_TYPE_0 128 

size_t
inet6_rthdr_space(int type, int seg)
{
	switch (type) {
	case IPV6_RTHDR_TYPE_0:
		if (seg < 1 || seg > 23)
			return (0);
#ifdef COMPAT_RFC2292
		return (CMSG_SPACE(sizeof(struct in6_addr) * (seg - 1) +
		    sizeof(struct ip6_rthdr0)));
#else
		return (CMSG_SPACE(sizeof(struct in6_addr) * seg +
		    sizeof(struct ip6_rthdr0)));
#endif 
	default:
		return (0);
	}
}
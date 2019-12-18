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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {scalar_t__ sa_len; scalar_t__ sa_family; } ;
struct rt_addrinfo {int rti_addrs; struct sockaddr** rti_info; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int RTAX_MAX ; 
 scalar_t__ SA_SIZE (struct sockaddr*) ; 
 int /*<<< orphan*/  V_ip6_use_defzone ; 
 int /*<<< orphan*/  sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 struct sockaddr sa_zero ; 

__attribute__((used)) static int
rt_xaddrs(caddr_t cp, caddr_t cplim, struct rt_addrinfo *rtinfo)
{
	struct sockaddr *sa;
	int i;

	for (i = 0; i < RTAX_MAX && cp < cplim; i++) {
		if ((rtinfo->rti_addrs & (1 << i)) == 0)
			continue;
		sa = (struct sockaddr *)cp;
		/*
		 * It won't fit.
		 */
		if (cp + sa->sa_len > cplim)
			return (EINVAL);
		/*
		 * there are no more.. quit now
		 * If there are more bits, they are in error.
		 * I've seen this. route(1) can evidently generate these. 
		 * This causes kernel to core dump.
		 * for compatibility, If we see this, point to a safe address.
		 */
		if (sa->sa_len == 0) {
			rtinfo->rti_info[i] = &sa_zero;
			return (0); /* should be EINVAL but for compat */
		}
		/* accept it */
#ifdef INET6
		if (sa->sa_family == AF_INET6)
			sa6_embedscope((struct sockaddr_in6 *)sa,
			    V_ip6_use_defzone);
#endif
		rtinfo->rti_info[i] = sa;
		cp += SA_SIZE(sa);
	}
	return (0);
}
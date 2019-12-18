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
struct ip6_rthdr {int ip6r_type; } ;
struct in6_addr {int dummy; } ;
struct cmsghdr {void* cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 void* CMSG_LEN (int) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_RTHDR ; 
#define  IPV6_RTHDR_TYPE_0 128 
 int /*<<< orphan*/  bzero (struct ip6_rthdr*,int) ; 

struct cmsghdr *
inet6_rthdr_init(void *bp, int type)
{
	struct cmsghdr *ch = (struct cmsghdr *)bp;
	struct ip6_rthdr *rthdr;

	rthdr = (struct ip6_rthdr *)CMSG_DATA(ch);

	ch->cmsg_level = IPPROTO_IPV6;
	ch->cmsg_type = IPV6_RTHDR;

	switch (type) {
	case IPV6_RTHDR_TYPE_0:
#ifdef COMPAT_RFC2292
		ch->cmsg_len = CMSG_LEN(sizeof(struct ip6_rthdr0) -
		    sizeof(struct in6_addr));
#else
		ch->cmsg_len = CMSG_LEN(sizeof(struct ip6_rthdr0));
#endif 

		bzero(rthdr, sizeof(struct ip6_rthdr0));
		rthdr->ip6r_type = IPV6_RTHDR_TYPE_0;
		return (ch);
	default:
		return (NULL);
	}
}
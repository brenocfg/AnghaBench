#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  cookie_t ;
struct TYPE_5__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in4; } ;
struct TYPE_4__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in4; } ;
struct TYPE_6__ {int version; int /*<<< orphan*/  initiator; TYPE_2__ raddr; TYPE_1__ iaddr; } ;

/* Variables and functions */
 int IP_V (struct ip const*) ; 
 int MAXINITIATORS ; 
 int /*<<< orphan*/  UNALIGNED_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int cookie_find (int /*<<< orphan*/ *) ; 
 TYPE_3__* cookiecache ; 
 size_t ninitiator ; 

__attribute__((used)) static void
cookie_record(cookie_t *in, const u_char *bp2)
{
	int i;
	const struct ip *ip;
	const struct ip6_hdr *ip6;

	i = cookie_find(in);
	if (0 <= i) {
		ninitiator = (i + 1) % MAXINITIATORS;
		return;
	}

	ip = (const struct ip *)bp2;
	switch (IP_V(ip)) {
	case 4:
		cookiecache[ninitiator].version = 4;
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].iaddr.in4, &ip->ip_src, sizeof(struct in_addr));
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].raddr.in4, &ip->ip_dst, sizeof(struct in_addr));
		break;
	case 6:
		ip6 = (const struct ip6_hdr *)bp2;
		cookiecache[ninitiator].version = 6;
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].iaddr.in6, &ip6->ip6_src, sizeof(struct in6_addr));
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].raddr.in6, &ip6->ip6_dst, sizeof(struct in6_addr));
		break;
	default:
		return;
	}
	UNALIGNED_MEMCPY(&cookiecache[ninitiator].initiator, in, sizeof(*in));
	ninitiator = (ninitiator + 1) % MAXINITIATORS;
}
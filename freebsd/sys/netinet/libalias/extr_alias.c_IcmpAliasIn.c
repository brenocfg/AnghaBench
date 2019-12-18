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
struct libalias {int packetAliasMode; } ;
struct ip {int dummy; } ;
struct icmp {int icmp_type; int /*<<< orphan*/  icmp_code; } ;

/* Variables and functions */
#define  ICMP_ECHO 135 
#define  ICMP_ECHOREPLY 134 
#define  ICMP_PARAMPROB 133 
#define  ICMP_SOURCEQUENCH 132 
#define  ICMP_TIMXCEED 131 
#define  ICMP_TSTAMP 130 
#define  ICMP_TSTAMPREPLY 129 
#define  ICMP_UNREACH 128 
 int IcmpAliasIn1 (struct libalias*,struct ip*) ; 
 int IcmpAliasIn2 (struct libalias*,struct ip*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int PKT_ALIAS_IGNORED ; 
 int PKT_ALIAS_OK ; 
 int PKT_ALIAS_PROXY_ONLY ; 
 scalar_t__ ip_next (struct ip*) ; 

__attribute__((used)) static int
IcmpAliasIn(struct libalias *la, struct ip *pip)
{
	int iresult;
	struct icmp *ic;

	LIBALIAS_LOCK_ASSERT(la);
/* Return if proxy-only mode is enabled */
	if (la->packetAliasMode & PKT_ALIAS_PROXY_ONLY)
		return (PKT_ALIAS_OK);

	ic = (struct icmp *)ip_next(pip);

	iresult = PKT_ALIAS_IGNORED;
	switch (ic->icmp_type) {
	case ICMP_ECHOREPLY:
	case ICMP_TSTAMPREPLY:
		if (ic->icmp_code == 0) {
			iresult = IcmpAliasIn1(la, pip);
		}
		break;
	case ICMP_UNREACH:
	case ICMP_SOURCEQUENCH:
	case ICMP_TIMXCEED:
	case ICMP_PARAMPROB:
		iresult = IcmpAliasIn2(la, pip);
		break;
	case ICMP_ECHO:
	case ICMP_TSTAMP:
		iresult = IcmpAliasIn1(la, pip);
		break;
	}
	return (iresult);
}
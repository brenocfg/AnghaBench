#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct libalias {int dummy; } ;
struct in_addr {int dummy; } ;
struct ip {struct in_addr ip_src; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/  ip_dst; } ;
struct alias_link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gh_call_id; } ;
typedef  TYPE_1__ GreHdr ;

/* Variables and functions */
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,struct in_addr*,struct in_addr*,int) ; 
 struct alias_link* FindPptpOutByPeerCallId (struct libalias*,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct in_addr GetAliasAddress (struct alias_link*) ; 
 int PPTP_INIT_MASK ; 
 int PPTP_INIT_VALUE ; 
 scalar_t__ ip_next (struct ip*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
AliasHandlePptpGreOut(struct libalias *la, struct ip *pip)
{
	GreHdr *gr;
	struct alias_link *lnk;

	gr = (GreHdr *) ip_next(pip);

	/* Check GRE header bits. */
	if ((ntohl(*((u_int32_t *) gr)) & PPTP_INIT_MASK) != PPTP_INIT_VALUE)
		return (-1);

	lnk = FindPptpOutByPeerCallId(la, pip->ip_src, pip->ip_dst, gr->gh_call_id);
	if (lnk != NULL) {
		struct in_addr alias_addr = GetAliasAddress(lnk);

		/* Change source IP address. */
		DifferentialChecksum(&pip->ip_sum,
		    &alias_addr, &pip->ip_src, 2);
		pip->ip_src = alias_addr;
	}
	return (0);
}
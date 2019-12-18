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
typedef  scalar_t__ u_int32_t ;
struct udphdr {int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_ulen; } ;
struct libalias {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_src; } ;
struct cu_header {scalar_t__ addr; } ;
struct alias_link {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;

/* Variables and functions */
 struct alias_link* FindUdpTcpOut (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ GetAliasAddress (struct alias_link*) ; 
 int /*<<< orphan*/  GetDestAddress (struct alias_link*) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PunchFWHole (struct alias_link*) ; 
 struct udphdr* ip_next (struct ip*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct cu_header* udp_next (struct udphdr*) ; 

__attribute__((used)) static void
AliasHandleCUSeeMeOut(struct libalias *la, struct ip *pip, struct alias_link *lnk)
{
	struct udphdr *ud = ip_next(pip);

	if (ntohs(ud->uh_ulen) - sizeof(struct udphdr) >= sizeof(struct cu_header)) {
		struct cu_header *cu;
		struct alias_link *cu_lnk;

		cu = udp_next(ud);
		if (cu->addr)
			cu->addr = (u_int32_t) GetAliasAddress(lnk).s_addr;

		cu_lnk = FindUdpTcpOut(la, pip->ip_src, GetDestAddress(lnk),
		    ud->uh_dport, 0, IPPROTO_UDP, 1);

#ifndef NO_FW_PUNCH
		if (cu_lnk)
			PunchFWHole(cu_lnk);
#endif
	}
}
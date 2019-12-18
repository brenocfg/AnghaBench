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
struct udphdr {int /*<<< orphan*/  uh_ulen; } ;
struct oc_header {int client_count; } ;
struct libalias {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct ip {TYPE_1__ ip_dst; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct cu_header {int /*<<< orphan*/  data_type; scalar_t__ dest_addr; } ;
struct client_info {scalar_t__ address; } ;

/* Variables and functions */
 struct udphdr* ip_next (struct ip*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct cu_header* udp_next (struct udphdr*) ; 

__attribute__((used)) static void
AliasHandleCUSeeMeIn(struct libalias *la, struct ip *pip, struct in_addr original_addr)
{
	struct in_addr alias_addr;
	struct udphdr *ud;
	struct cu_header *cu;
	struct oc_header *oc;
	struct client_info *ci;
	char *end;
	int i;

	(void)la;
	alias_addr.s_addr = pip->ip_dst.s_addr;
	ud = ip_next(pip);
	cu = udp_next(ud);
	oc = (struct oc_header *)(cu + 1);
	ci = (struct client_info *)(oc + 1);
	end = (char *)ud + ntohs(ud->uh_ulen);

	if ((char *)oc <= end) {
		if (cu->dest_addr)
			cu->dest_addr = (u_int32_t) original_addr.s_addr;
		if (ntohs(cu->data_type) == 101)
			/* Find and change our address */
			for (i = 0; (char *)(ci + 1) <= end && i < oc->client_count; i++, ci++)
				if (ci->address == (u_int32_t) alias_addr.s_addr) {
					ci->address = (u_int32_t) original_addr.s_addr;
					break;
				}
	}
}
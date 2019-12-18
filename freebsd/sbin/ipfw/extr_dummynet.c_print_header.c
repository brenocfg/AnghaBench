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
struct ipfw_flow_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_IP6_FLOW_ID (struct ipfw_flow_id*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_header(struct ipfw_flow_id *id)
{
	if (!IS_IP6_FLOW_ID(id))
		printf("BKT Prot ___Source IP/port____ "
		    "____Dest. IP/port____ "
		    "Tot_pkt/bytes Pkt/Byte Drp\n");
	else
		printf("BKT ___Prot___ _flow-id_ "
		    "______________Source IPv6/port_______________ "
		    "_______________Dest. IPv6/port_______________ "
		    "Tot_pkt/bytes Pkt/Byte Drp\n");
}
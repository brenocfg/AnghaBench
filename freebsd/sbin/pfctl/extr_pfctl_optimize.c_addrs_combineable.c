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
struct TYPE_2__ {scalar_t__ type; } ;
struct pf_rule_addr {scalar_t__ neg; scalar_t__ port_op; scalar_t__* port; TYPE_1__ addr; } ;

/* Variables and functions */
 scalar_t__ PF_ADDR_ADDRMASK ; 

int
addrs_combineable(struct pf_rule_addr *a, struct pf_rule_addr *b)
{
	if (a->addr.type != PF_ADDR_ADDRMASK ||
	    b->addr.type != PF_ADDR_ADDRMASK)
		return (0);
	if (a->neg != b->neg || a->port_op != b->port_op ||
	    a->port[0] != b->port[0] || a->port[1] != b->port[1])
		return (0);
	return (1);
}
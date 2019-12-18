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
struct TYPE_2__ {scalar_t__ port_op; scalar_t__* port; } ;
struct pf_rule {TYPE_1__ src; } ;

/* Variables and functions */
 scalar_t__ PF_OP_NONE ; 

int
skip_cmp_src_port(struct pf_rule *a, struct pf_rule *b)
{
	if (a->src.port_op == PF_OP_NONE || a->src.port_op != b->src.port_op ||
	    a->src.port[0] != b->src.port[0] ||
	    a->src.port[1] != b->src.port[1])
		return (1);
	/* XXX if (a->proto != b->proto && a->proto != 0 && b->proto != 0
	 *    && (a->proto == IPPROTO_TCP || a->proto == IPPROTO_UDP ||
	 *    a->proto == IPPROTO_ICMP
	 *	return (1);
	 */
	return (0);
}
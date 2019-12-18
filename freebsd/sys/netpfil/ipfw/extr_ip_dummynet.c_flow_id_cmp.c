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
struct ipfw_flow_id {scalar_t__ dst_ip; scalar_t__ src_ip; scalar_t__ dst_port; scalar_t__ src_port; scalar_t__ proto; scalar_t__ extra; scalar_t__ flow_id6; int /*<<< orphan*/  src_ip6; int /*<<< orphan*/  dst_ip6; } ;

/* Variables and functions */
 int IS_IP6_FLOW_ID (struct ipfw_flow_id*) ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
flow_id_cmp(struct ipfw_flow_id *id1, struct ipfw_flow_id *id2)
{
	int is_v6 = IS_IP6_FLOW_ID(id1);

	if (!is_v6) {
	    if (IS_IP6_FLOW_ID(id2))
		return 1; /* different address families */

	    return (id1->dst_ip == id2->dst_ip &&
		    id1->src_ip == id2->src_ip &&
		    id1->dst_port == id2->dst_port &&
		    id1->src_port == id2->src_port &&
		    id1->proto == id2->proto &&
		    id1->extra == id2->extra) ? 0 : 1;
	}
	/* the ipv6 case */
	return (
	    !bcmp(&id1->dst_ip6,&id2->dst_ip6, sizeof(id1->dst_ip6)) &&
	    !bcmp(&id1->src_ip6,&id2->src_ip6, sizeof(id1->src_ip6)) &&
	    id1->dst_port == id2->dst_port &&
	    id1->src_port == id2->src_port &&
	    id1->proto == id2->proto &&
	    id1->extra == id2->extra &&
	    id1->flow_id6 == id2->flow_id6) ? 0 : 1;
}
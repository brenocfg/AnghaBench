#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* __u6_addr32; } ;
struct TYPE_8__ {TYPE_3__ __u6_addr; } ;
struct TYPE_5__ {scalar_t__* __u6_addr32; } ;
struct TYPE_6__ {TYPE_1__ __u6_addr; } ;
struct ipfw_flow_id {scalar_t__ src_ip; scalar_t__ dst_ip; scalar_t__ flow_id6; TYPE_4__ src_ip6; TYPE_2__ dst_ip6; scalar_t__ extra; scalar_t__ proto; scalar_t__ src_port; scalar_t__ dst_port; } ;

/* Variables and functions */
 scalar_t__ IS_IP6_FLOW_ID (struct ipfw_flow_id*) ; 

__attribute__((used)) static int
nonzero_mask(struct ipfw_flow_id *m)
{
	if (m->dst_port || m->src_port || m->proto || m->extra)
		return 1;
	if (IS_IP6_FLOW_ID(m)) {
		return
			m->dst_ip6.__u6_addr.__u6_addr32[0] ||
			m->dst_ip6.__u6_addr.__u6_addr32[1] ||
			m->dst_ip6.__u6_addr.__u6_addr32[2] ||
			m->dst_ip6.__u6_addr.__u6_addr32[3] ||
			m->src_ip6.__u6_addr.__u6_addr32[0] ||
			m->src_ip6.__u6_addr.__u6_addr32[1] ||
			m->src_ip6.__u6_addr.__u6_addr32[2] ||
			m->src_ip6.__u6_addr.__u6_addr32[3] ||
			m->flow_id6;
	} else {
		return m->dst_ip || m->src_ip;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ip_fw {int /*<<< orphan*/  set; } ;
struct dyn_ipv4_state {int type; int /*<<< orphan*/  proto; TYPE_6__* data; int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  kidx; TYPE_3__* limit; } ;
struct TYPE_8__ {int addr_type; scalar_t__ extra; scalar_t__ flow_id6; int /*<<< orphan*/  src_ip6; int /*<<< orphan*/  dst_ip6; scalar_t__ _flags; int /*<<< orphan*/  proto; int /*<<< orphan*/  fib; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  dst_ip; } ;
struct TYPE_9__ {TYPE_1__ id; } ;
typedef  TYPE_2__ ipfw_dyn_rule ;
struct TYPE_11__ {int /*<<< orphan*/  fibnum; struct ip_fw* parent; } ;
struct TYPE_10__ {struct ip_fw* parent; } ;

/* Variables and functions */
 int O_LIMIT ; 
#define  O_LIMIT_PARENT 128 
 int /*<<< orphan*/  dyn_export_data (TYPE_6__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dyn_export_parent (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dyn_export_ipv4_state(const struct dyn_ipv4_state *s, ipfw_dyn_rule *dst)
{
	struct ip_fw *rule;

	switch (s->type) {
	case O_LIMIT_PARENT:
		rule = s->limit->parent;
		dyn_export_parent(s->limit, s->kidx, rule->set, dst);
		break;
	default:
		rule = s->data->parent;
		if (s->type == O_LIMIT)
			rule = ((struct dyn_ipv4_state *)rule)->limit->parent;
		dyn_export_data(s->data, s->kidx, s->type, rule->set, dst);
	}

	dst->id.dst_ip = s->dst;
	dst->id.src_ip = s->src;
	dst->id.dst_port = s->dport;
	dst->id.src_port = s->sport;
	dst->id.fib = s->data->fibnum;
	dst->id.proto = s->proto;
	dst->id._flags = 0;
	dst->id.addr_type = 4;

	memset(&dst->id.dst_ip6, 0, sizeof(dst->id.dst_ip6));
	memset(&dst->id.src_ip6, 0, sizeof(dst->id.src_ip6));
	dst->id.flow_id6 = dst->id.extra = 0;
}
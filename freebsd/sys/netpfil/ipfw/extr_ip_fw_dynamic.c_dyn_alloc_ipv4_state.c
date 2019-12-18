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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ipfw_flow_id {int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  proto; } ;
struct dyn_ipv4_state {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  proto; int /*<<< orphan*/  kidx; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_dyn_ipv4_zone ; 
 struct dyn_ipv4_state* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dyn_ipv4_state *
dyn_alloc_ipv4_state(const struct ipfw_flow_id *pkt, uint16_t kidx,
    uint8_t type)
{
	struct dyn_ipv4_state *s;

	s = uma_zalloc(V_dyn_ipv4_zone, M_NOWAIT | M_ZERO);
	if (s == NULL)
		return (NULL);

	s->type = type;
	s->kidx = kidx;
	s->proto = pkt->proto;
	s->sport = pkt->src_port;
	s->dport = pkt->dst_port;
	s->src = pkt->src_ip;
	s->dst = pkt->dst_ip;
	return (s);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct netflow_v9_record_ipv6_tcp {int /*<<< orphan*/  dst_as; int /*<<< orphan*/  src_as; int /*<<< orphan*/  src_mask; int /*<<< orphan*/  dst_mask; int /*<<< orphan*/  tos; int /*<<< orphan*/  prot; int /*<<< orphan*/  flags; int /*<<< orphan*/  d_port; int /*<<< orphan*/  s_port; void* last; void* first; void* o_octets; void* o_packets; void* i_octets; void* i_packets; void* o_ifx; void* i_ifx; int /*<<< orphan*/  next_hop; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct netflow_v9_record_ipv4_tcp {int /*<<< orphan*/  dst_as; int /*<<< orphan*/  src_as; int /*<<< orphan*/  src_mask; int /*<<< orphan*/  dst_mask; int /*<<< orphan*/  tos; int /*<<< orphan*/  prot; int /*<<< orphan*/  flags; int /*<<< orphan*/  d_port; int /*<<< orphan*/  s_port; void* last; void* first; void* o_octets; void* o_packets; void* i_octets; void* i_packets; void* o_ifx; void* i_ifx; int /*<<< orphan*/  next_hop; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct TYPE_14__ {struct netflow_v9_record_ipv6_tcp v6_tcp; struct netflow_v9_record_ipv4_tcp v4_tcp; } ;
struct netflow_v9_record_general {TYPE_5__ rec; } ;
struct netflow_v9_packet_opt {int flow_type; int /*<<< orphan*/  mtu; int /*<<< orphan*/  count; scalar_t__ flow_header; } ;
struct netflow_v9_flowset_header {scalar_t__ length; void* id; } ;
struct mbuf {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {int flow_type; int /*<<< orphan*/  r_tos; int /*<<< orphan*/  r_ip_p; int /*<<< orphan*/  r_dport; int /*<<< orphan*/  r_sport; TYPE_2__ r_dst; TYPE_1__ r_src; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct flow_entry_data {int /*<<< orphan*/  src_mask; int /*<<< orphan*/  dst_mask; TYPE_4__ r; int /*<<< orphan*/  tcp_flags; int /*<<< orphan*/  last; int /*<<< orphan*/  first; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; scalar_t__ fle_o_ifx; scalar_t__ fle_i_ifx; TYPE_3__ next_hop; } ;
struct flow_entry {int /*<<< orphan*/  f; } ;
struct TYPE_16__ {int /*<<< orphan*/  r_dst6; } ;
struct TYPE_15__ {int /*<<< orphan*/  r_src6; } ;
struct TYPE_18__ {int /*<<< orphan*/  r_tos; int /*<<< orphan*/  r_ip_p; int /*<<< orphan*/  r_dport; int /*<<< orphan*/  r_sport; TYPE_7__ dst; TYPE_6__ src; } ;
struct TYPE_17__ {int /*<<< orphan*/  next_hop6; } ;
struct flow6_entry_data {int /*<<< orphan*/  src_mask; int /*<<< orphan*/  dst_mask; TYPE_9__ r; int /*<<< orphan*/  tcp_flags; int /*<<< orphan*/  last; int /*<<< orphan*/  first; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; scalar_t__ fle_o_ifx; scalar_t__ fle_i_ifx; TYPE_8__ n; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  fsh ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  KTR_NET ; 
 int /*<<< orphan*/  MILLIUPTIME (int /*<<< orphan*/ ) ; 
#define  NETFLOW_V9_FLOW_V4_L4 129 
#define  NETFLOW_V9_FLOW_V6_L4 128 
 scalar_t__ NETFLOW_V9_MAX_RESERVED_FLOWSET ; 
 struct mbuf* NGI_M (int /*<<< orphan*/ ) ; 
 scalar_t__ _NETFLOW_V9_MAX_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_flowset (struct mbuf*,struct netflow_v9_packet_opt*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 int m_append (struct mbuf*,size_t,void*) ; 
 scalar_t__ m_pktlen (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
export9_add(item_p item, struct netflow_v9_packet_opt *t, struct flow_entry *fle)
{
	size_t len = 0;
	struct netflow_v9_flowset_header fsh;
	struct netflow_v9_record_general rg;
	struct mbuf *m = NGI_M(item);
	uint16_t flow_type;
	struct flow_entry_data *fed;
#ifdef INET6	
	struct flow6_entry_data *fed6;
#endif
	if (t == NULL) {
		CTR0(KTR_NET, "ng_netflow: V9 export packet without tag!");
		return (0);
	}

	/* Prepare flow record */
	fed = (struct flow_entry_data *)&fle->f;
#ifdef INET6
	fed6 = (struct flow6_entry_data *)&fle->f;
#endif
	/* We can use flow_type field since fle6 offset is equal to fle */
	flow_type = fed->r.flow_type;

	switch (flow_type) {
	case NETFLOW_V9_FLOW_V4_L4:
	{
		/* IPv4 TCP/UDP/[SCTP] */
		struct netflow_v9_record_ipv4_tcp *rec = &rg.rec.v4_tcp;
		
		rec->src_addr = fed->r.r_src.s_addr;
		rec->dst_addr = fed->r.r_dst.s_addr;
		rec->next_hop = fed->next_hop.s_addr;
		rec->i_ifx    = htons(fed->fle_i_ifx);
		rec->o_ifx    = htons(fed->fle_o_ifx);
		rec->i_packets  = htonl(fed->packets);
		rec->i_octets   = htonl(fed->bytes);
		rec->o_packets  = htonl(0);
		rec->o_octets   = htonl(0);
		rec->first    = htonl(MILLIUPTIME(fed->first));
		rec->last     = htonl(MILLIUPTIME(fed->last));
		rec->s_port   = fed->r.r_sport;
		rec->d_port   = fed->r.r_dport;
		rec->flags    = fed->tcp_flags;
		rec->prot     = fed->r.r_ip_p;
		rec->tos      = fed->r.r_tos;
		rec->dst_mask = fed->dst_mask;
		rec->src_mask = fed->src_mask;

		/* Not supported fields. */
		rec->src_as = rec->dst_as = 0;

		len = sizeof(struct netflow_v9_record_ipv4_tcp);
		break;
	}
#ifdef INET6	
	case NETFLOW_V9_FLOW_V6_L4:
	{
		/* IPv6 TCP/UDP/[SCTP] */
		struct netflow_v9_record_ipv6_tcp *rec = &rg.rec.v6_tcp;

		rec->src_addr = fed6->r.src.r_src6;
		rec->dst_addr = fed6->r.dst.r_dst6;
		rec->next_hop = fed6->n.next_hop6;
		rec->i_ifx    = htons(fed6->fle_i_ifx);
		rec->o_ifx    = htons(fed6->fle_o_ifx);
		rec->i_packets  = htonl(fed6->packets);
		rec->i_octets   = htonl(fed6->bytes);
		rec->o_packets  = htonl(0);
		rec->o_octets   = htonl(0);
		rec->first    = htonl(MILLIUPTIME(fed6->first));
		rec->last     = htonl(MILLIUPTIME(fed6->last));
		rec->s_port   = fed6->r.r_sport;
		rec->d_port   = fed6->r.r_dport;
		rec->flags    = fed6->tcp_flags;
		rec->prot     = fed6->r.r_ip_p;
		rec->tos      = fed6->r.r_tos;
		rec->dst_mask = fed6->dst_mask;
		rec->src_mask = fed6->src_mask;

		/* Not supported fields. */
		rec->src_as = rec->dst_as = 0;

		len = sizeof(struct netflow_v9_record_ipv6_tcp);
		break;
	}
#endif	
	default:
	{
		CTR1(KTR_NET, "export9_add(): Don't know what to do with %d flow type!", flow_type);
		return (0);
	}
	}

	/* Check if new records has the same template */
	if (flow_type != t->flow_type) {
		/* close old flowset */
		if (t->flow_type != 0)
			close_flowset(m, t);

		t->flow_type = flow_type;
		t->flow_header = m_pktlen(m);

		/* Generate data flowset ID */
		fsh.id = htons(NETFLOW_V9_MAX_RESERVED_FLOWSET + flow_type);
		fsh.length = 0;

		/* m_append should not fail since all data is already allocated */
		if (m_append(m, sizeof(fsh), (void *)&fsh) != 1)
			panic("ng_netflow: m_append() failed");
		
	}

	if (m_append(m, len, (void *)&rg.rec) != 1)
		panic("ng_netflow: m_append() failed");

	t->count++;

	if (m_pktlen(m) + sizeof(struct netflow_v9_record_general) + sizeof(struct netflow_v9_flowset_header) >= _NETFLOW_V9_MAX_SIZE(t->mtu))
		return (1); /* end of datagram */
	return (0);
}
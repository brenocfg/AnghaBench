#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct sa_handle {int dummy; } ;
struct query_params {int /*<<< orphan*/  proxy_join; int /*<<< orphan*/  join_state; int /*<<< orphan*/  scope; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  tclass; int /*<<< orphan*/  pkt_life; int /*<<< orphan*/  rate; int /*<<< orphan*/  mtu; int /*<<< orphan*/  qkey; int /*<<< orphan*/  mlid; int /*<<< orphan*/  gid; int /*<<< orphan*/  mgid; } ;
struct query_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  mr ;
typedef  int /*<<< orphan*/  ib_net64_t ;
struct TYPE_4__ {int mlid; int qkey; int tclass; int pkey; int scope_state; int proxy_join; int /*<<< orphan*/  sl_flow_hop; int /*<<< orphan*/  pkt_life; int /*<<< orphan*/  rate; int /*<<< orphan*/  mtu; int /*<<< orphan*/  port_gid; int /*<<< orphan*/  mgid; } ;
typedef  TYPE_1__ ib_member_rec_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_SET_GID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_AND_SET_VAL (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_AND_SET_VAL_AND_SEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOW ; 
 int /*<<< orphan*/  HOP ; 
 int /*<<< orphan*/  IB_SA_ATTR_MCRECORD ; 
 int /*<<< orphan*/  JOIN_STATE ; 
 int /*<<< orphan*/  LIFE ; 
 int /*<<< orphan*/  MCR ; 
 int /*<<< orphan*/  MGID ; 
 int /*<<< orphan*/  MLID ; 
 int /*<<< orphan*/  MTU ; 
 int /*<<< orphan*/  PKEY ; 
 int /*<<< orphan*/  PORT_GID ; 
 int /*<<< orphan*/  PROXY ; 
 int /*<<< orphan*/  QKEY ; 
 int /*<<< orphan*/  RATE ; 
 int /*<<< orphan*/  SCOPE ; 
 int /*<<< orphan*/  SL ; 
 int /*<<< orphan*/  TCLASS ; 
 int /*<<< orphan*/  _SEL ; 
 int /*<<< orphan*/  cl_ntoh32 (int) ; 
 int /*<<< orphan*/  dump_one_mcmember_record ; 
 int get_and_dump_any_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,struct query_params*) ; 
 int /*<<< orphan*/  ib_member_set_sl_flow_hop (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int query_mcmember_records(const struct query_cmd *q,
				  struct sa_handle * h, struct query_params *p,
				  int argc, char *argv[])
{
	ib_member_rec_t mr;
	ib_net64_t comp_mask = 0;
	uint32_t flow = 0;
	uint8_t sl = 0, hop = 0, scope = 0;

	memset(&mr, 0, sizeof(mr));
	CHECK_AND_SET_GID(p->mgid, mr.mgid, MCR, MGID);
	CHECK_AND_SET_GID(p->gid, mr.port_gid, MCR, PORT_GID);
	CHECK_AND_SET_VAL(p->mlid, 16, 0, mr.mlid, MCR, MLID);
	CHECK_AND_SET_VAL(p->qkey, 32, 0, mr.qkey, MCR, QKEY);
	CHECK_AND_SET_VAL_AND_SEL(p->mtu, mr.mtu, MCR, MTU, _SEL);
	CHECK_AND_SET_VAL_AND_SEL(p->rate, mr.rate, MCR, RATE, _SEL);
	CHECK_AND_SET_VAL_AND_SEL(p->pkt_life, mr.pkt_life, MCR, LIFE, _SEL);
	CHECK_AND_SET_VAL(p->tclass, 8, 0, mr.tclass, MCR, TCLASS);
	CHECK_AND_SET_VAL(p->pkey, 16, 0, mr.pkey, MCR, PKEY);
	CHECK_AND_SET_VAL(p->sl, 8, -1, sl, MCR, SL);
	CHECK_AND_SET_VAL(p->flow_label, 32, 0, flow, MCR, FLOW);
	CHECK_AND_SET_VAL(p->hop_limit, 8, 0, hop, MCR, HOP);
	/* pass flow in host order as expected by function */
	mr.sl_flow_hop = ib_member_set_sl_flow_hop(sl, cl_ntoh32(flow), hop);
	CHECK_AND_SET_VAL(p->scope, 8, 0, scope, MCR, SCOPE);
	CHECK_AND_SET_VAL(p->join_state, 8, 0, mr.scope_state, MCR, JOIN_STATE);
	mr.scope_state |= scope << 4;
	CHECK_AND_SET_VAL(p->proxy_join, 8, -1, mr.proxy_join, MCR, PROXY);

	return get_and_dump_any_records(h, IB_SA_ATTR_MCRECORD, 0, comp_mask,
					&mr, sizeof(mr), dump_one_mcmember_record, p);
}
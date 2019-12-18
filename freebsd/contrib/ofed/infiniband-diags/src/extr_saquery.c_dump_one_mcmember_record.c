#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct query_params {int dummy; } ;
typedef  int /*<<< orphan*/  mgid ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {int mtu; int tclass; int rate; int pkt_life; int proxy_join; int /*<<< orphan*/  pkey; int /*<<< orphan*/  mlid; int /*<<< orphan*/  qkey; TYPE_2__ port_gid; TYPE_1__ mgid; int /*<<< orphan*/  scope_state; int /*<<< orphan*/  sl_flow_hop; } ;
typedef  TYPE_3__ ib_member_rec_t ;
typedef  int /*<<< orphan*/  gid ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int cl_ntoh32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_member_get_scope_state (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ib_member_get_sl_flow_hop (int /*<<< orphan*/ ,int*,int*,int*) ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void dump_one_mcmember_record(void *data, struct query_params *p)
{
	char mgid[INET6_ADDRSTRLEN], gid[INET6_ADDRSTRLEN];
	ib_member_rec_t *mr = data;
	uint32_t flow;
	uint8_t sl, hop, scope, join;
	ib_member_get_sl_flow_hop(mr->sl_flow_hop, &sl, &flow, &hop);
	ib_member_get_scope_state(mr->scope_state, &scope, &join);
	printf("MCMember Record dump:\n"
	       "\t\tMGID....................%s\n"
	       "\t\tPortGid.................%s\n"
	       "\t\tqkey....................0x%x\n"
	       "\t\tmlid....................0x%x\n"
	       "\t\tmtu.....................0x%x\n"
	       "\t\tTClass..................0x%x\n"
	       "\t\tpkey....................0x%x\n"
	       "\t\trate....................0x%x\n"
	       "\t\tpkt_life................0x%x\n"
	       "\t\tSL......................0x%x\n"
	       "\t\tFlowLabel...............0x%x\n"
	       "\t\tHopLimit................0x%x\n"
	       "\t\tScope...................0x%x\n"
	       "\t\tJoinState...............0x%x\n"
	       "\t\tProxyJoin...............0x%x\n",
	       inet_ntop(AF_INET6, mr->mgid.raw, mgid, sizeof(mgid)),
	       inet_ntop(AF_INET6, mr->port_gid.raw, gid, sizeof(gid)),
	       cl_ntoh32(mr->qkey), cl_ntoh16(mr->mlid), mr->mtu, mr->tclass,
	       cl_ntoh16(mr->pkey), mr->rate, mr->pkt_life, sl,
	       flow, hop, scope, join, mr->proxy_join);
}
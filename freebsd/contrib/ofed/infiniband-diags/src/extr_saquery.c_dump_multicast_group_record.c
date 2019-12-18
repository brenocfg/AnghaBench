#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct query_params {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {int mtu; int rate; int /*<<< orphan*/  pkey; int /*<<< orphan*/  mlid; TYPE_1__ mgid; int /*<<< orphan*/  sl_flow_hop; } ;
typedef  TYPE_2__ ib_member_rec_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_member_get_sl_flow_hop (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,int) ; 

__attribute__((used)) static void dump_multicast_group_record(void *data, struct query_params *p)
{
	char gid_str[INET6_ADDRSTRLEN];
	ib_member_rec_t *p_mcmr = data;
	uint8_t sl;
	ib_member_get_sl_flow_hop(p_mcmr->sl_flow_hop, &sl, NULL, NULL);
	printf("MCMemberRecord group dump:\n"
	       "\t\tMGID....................%s\n"
	       "\t\tMlid....................0x%X\n"
	       "\t\tMtu.....................0x%X\n"
	       "\t\tpkey....................0x%X\n"
	       "\t\tRate....................0x%X\n"
	       "\t\tSL......................0x%X\n",
	       inet_ntop(AF_INET6, p_mcmr->mgid.raw, gid_str, sizeof gid_str),
	       cl_ntoh16(p_mcmr->mlid),
	       p_mcmr->mtu, cl_ntoh16(p_mcmr->pkey), p_mcmr->rate, sl);
}
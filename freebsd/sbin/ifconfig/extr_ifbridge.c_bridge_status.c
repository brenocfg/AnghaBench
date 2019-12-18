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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct ifbrparam {int ifbrp_csize; int ifbrp_ctime; int ifbop_priority; int ifbop_protocol; int ifbop_hellotime; int ifbop_fwddelay; int ifbop_holdcount; int ifbop_maxage; int ifbop_root_path_cost; int ifbop_root_port; int /*<<< orphan*/  ifbop_designated_root; int /*<<< orphan*/  ifbop_bridgeid; } ;
struct ifbropreq {int ifbrp_csize; int ifbrp_ctime; int ifbop_priority; int ifbop_protocol; int ifbop_hellotime; int ifbop_fwddelay; int ifbop_holdcount; int ifbop_maxage; int ifbop_root_path_cost; int ifbop_root_port; int /*<<< orphan*/  ifbop_designated_root; int /*<<< orphan*/  ifbop_bridgeid; } ;
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  ifbp ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGCACHE ; 
 int /*<<< orphan*/  BRDGGTO ; 
 int /*<<< orphan*/  BRDGPARAM ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  PV2ID (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bridge_interfaces (int,char*) ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbrparam*,int,int /*<<< orphan*/ ) ; 
 char* ether_ntoa (struct ether_addr*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** stpproto ; 

__attribute__((used)) static void
bridge_status(int s)
{
	struct ifbropreq ifbp;
	struct ifbrparam param;
	u_int16_t pri;
	u_int8_t ht, fd, ma, hc, pro;
	u_int8_t lladdr[ETHER_ADDR_LEN];
	u_int16_t bprio;
	u_int32_t csize, ctime;

	if (do_cmd(s, BRDGGCACHE, &param, sizeof(param), 0) < 0)
		return;
	csize = param.ifbrp_csize;
	if (do_cmd(s, BRDGGTO, &param, sizeof(param), 0) < 0)
		return;
	ctime = param.ifbrp_ctime;
	if (do_cmd(s, BRDGPARAM, &ifbp, sizeof(ifbp), 0) < 0)
		return;
	pri = ifbp.ifbop_priority;
	pro = ifbp.ifbop_protocol;
	ht = ifbp.ifbop_hellotime;
	fd = ifbp.ifbop_fwddelay;
	hc = ifbp.ifbop_holdcount;
	ma = ifbp.ifbop_maxage;

	PV2ID(ifbp.ifbop_bridgeid, bprio, lladdr);
	printf("\tid %s priority %u hellotime %u fwddelay %u\n",
	    ether_ntoa((struct ether_addr *)lladdr), pri, ht, fd);
	printf("\tmaxage %u holdcnt %u proto %s maxaddr %u timeout %u\n",
	    ma, hc, stpproto[pro], csize, ctime);

	PV2ID(ifbp.ifbop_designated_root, bprio, lladdr);
	printf("\troot id %s priority %d ifcost %u port %u\n",
	    ether_ntoa((struct ether_addr *)lladdr), bprio,
	    ifbp.ifbop_root_path_cost, ifbp.ifbop_root_port & 0xfff);

	bridge_interfaces(s, "\tmember: ");

	return;

}
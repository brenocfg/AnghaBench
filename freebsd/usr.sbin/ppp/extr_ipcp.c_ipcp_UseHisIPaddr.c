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
struct TYPE_4__ {int /*<<< orphan*/  my_range; int /*<<< orphan*/  peer_range; int /*<<< orphan*/  peer_list; } ;
struct in_addr {int dummy; } ;
struct ipcp {TYPE_2__ cfg; struct in_addr peer_ip; } ;
struct TYPE_3__ {struct ipcp ipcp; } ;
struct bundle {TYPE_1__ ncp; } ;

/* Variables and functions */
 int ipcp_SetIPaddress (struct ipcp*,struct in_addr,struct in_addr) ; 
 int /*<<< orphan*/  iplist_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  ncprange_getip4addr (int /*<<< orphan*/ *,struct in_addr*) ; 
 int /*<<< orphan*/  ncprange_setip4host (int /*<<< orphan*/ *,struct in_addr) ; 

int
ipcp_UseHisIPaddr(struct bundle *bundle, struct in_addr hisaddr)
{
  struct ipcp *ipcp = &bundle->ncp.ipcp;
  struct in_addr myaddr;

  memset(&ipcp->cfg.peer_range, '\0', sizeof ipcp->cfg.peer_range);
  iplist_reset(&ipcp->cfg.peer_list);
  ipcp->peer_ip = hisaddr;
  ncprange_setip4host(&ipcp->cfg.peer_range, hisaddr);
  ncprange_getip4addr(&ipcp->cfg.my_range, &myaddr);

  return ipcp_SetIPaddress(ipcp, myaddr, hisaddr);
}
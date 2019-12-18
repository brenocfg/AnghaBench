#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ncprange {int dummy; } ;
struct cmdargs {int argc; int argn; TYPE_5__* bundle; TYPE_4__* cmd; int /*<<< orphan*/ * argv; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dns; } ;
struct TYPE_10__ {TYPE_2__ ns; int /*<<< orphan*/  peer_ip; int /*<<< orphan*/  my_ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  hisaddr; int /*<<< orphan*/  myaddr; } ;
struct TYPE_13__ {int /*<<< orphan*/  route; TYPE_3__ ipcp; TYPE_1__ ipv6cp; } ;
struct TYPE_12__ {TYPE_7__ ncp; } ;
struct TYPE_11__ {scalar_t__ args; } ;

/* Variables and functions */
 int ROUTE_DSTDNS0 ; 
 int ROUTE_DSTDNS1 ; 
 int ROUTE_DSTHISADDR ; 
 int ROUTE_DSTHISADDR6 ; 
 int ROUTE_DSTMYADDR ; 
 int ROUTE_DSTMYADDR6 ; 
 int ROUTE_STATIC ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  ncprange_aton (struct ncprange*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncprange_sethost (struct ncprange*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncprange_setip4host (struct ncprange*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_Delete (int /*<<< orphan*/ *,int,struct ncprange*) ; 
 int /*<<< orphan*/  route_DeleteAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  route_IfDelete (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_Set (TYPE_5__*,int /*<<< orphan*/ ,struct ncprange*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
DeleteCommand(struct cmdargs const *arg)
{
  struct ncprange dest;
  int addrs;

  if (arg->argc == arg->argn+1) {
    if(strcasecmp(arg->argv[arg->argn], "all") == 0) {
      route_IfDelete(arg->bundle, 0);
      route_DeleteAll(&arg->bundle->ncp.route);
    } else {
      addrs = 0;
      if (strcasecmp(arg->argv[arg->argn], "MYADDR") == 0) {
        ncprange_setip4host(&dest, arg->bundle->ncp.ipcp.my_ip);
        addrs = ROUTE_DSTMYADDR;
#ifndef NOINET6
      } else if (strcasecmp(arg->argv[arg->argn], "MYADDR6") == 0) {
        ncprange_sethost(&dest, &arg->bundle->ncp.ipv6cp.myaddr);
        addrs = ROUTE_DSTMYADDR6;
#endif
      } else if (strcasecmp(arg->argv[arg->argn], "HISADDR") == 0) {
        ncprange_setip4host(&dest, arg->bundle->ncp.ipcp.peer_ip);
        addrs = ROUTE_DSTHISADDR;
#ifndef NOINET6
      } else if (strcasecmp(arg->argv[arg->argn], "HISADDR6") == 0) {
        ncprange_sethost(&dest, &arg->bundle->ncp.ipv6cp.hisaddr);
        addrs = ROUTE_DSTHISADDR6;
#endif
      } else if (strcasecmp(arg->argv[arg->argn], "DNS0") == 0) {
        ncprange_setip4host(&dest, arg->bundle->ncp.ipcp.ns.dns[0]);
        addrs = ROUTE_DSTDNS0;
      } else if (strcasecmp(arg->argv[arg->argn], "DNS1") == 0) {
        ncprange_setip4host(&dest, arg->bundle->ncp.ipcp.ns.dns[1]);
        addrs = ROUTE_DSTDNS1;
      } else {
        ncprange_aton(&dest, &arg->bundle->ncp, arg->argv[arg->argn]);
        addrs = ROUTE_STATIC;
      }
      rt_Set(arg->bundle, RTM_DELETE, &dest, NULL, arg->cmd->args ? 1 : 0, 0);
      route_Delete(&arg->bundle->ncp.route, addrs, &dest);
    }
  } else
    return -1;

  return 0;
}
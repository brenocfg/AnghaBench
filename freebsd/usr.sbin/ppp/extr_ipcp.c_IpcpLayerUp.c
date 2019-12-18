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
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int maxreq; } ;
struct TYPE_16__ {TYPE_5__ fsm; } ;
struct TYPE_12__ {int /*<<< orphan*/  cslc; } ;
struct ipcp {int peer_compproto; TYPE_6__ cfg; int /*<<< orphan*/  throughput; int /*<<< orphan*/  ifmask; int /*<<< orphan*/  peer_ip; TYPE_2__ vj; int /*<<< orphan*/  my_ip; } ;
struct TYPE_14__ {int reqs; int naks; int rejs; } ;
struct fsm {TYPE_4__ more; TYPE_7__* bundle; TYPE_1__* link; } ;
struct TYPE_13__ {scalar_t__* file; } ;
struct TYPE_18__ {char* filterid; TYPE_3__ cfg; } ;
struct TYPE_17__ {TYPE_9__ radius; int /*<<< orphan*/  links; int /*<<< orphan*/  radacct; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINKUPFILE ; 
 int /*<<< orphan*/  LogIPCP ; 
 int PROTO_VJCOMP ; 
 int /*<<< orphan*/  RAD_START ; 
 char* bundle_GetLabel (TYPE_7__*) ; 
 struct ipcp* fsm2ipcp (struct fsm*) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_InterfaceUp (struct ipcp*) ; 
 int /*<<< orphan*/  log_DisplayPrompts () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  radius_Account (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_Account_Set_Ip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_StartTimer (TYPE_7__*) ; 
 int /*<<< orphan*/  sl_compress_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ system_Select (TYPE_7__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
IpcpLayerUp(struct fsm *fp)
{
  /* We're now up */
  struct ipcp *ipcp = fsm2ipcp(fp);
  char tbuff[16];

  log_Printf(LogIPCP, "%s: LayerUp.\n", fp->link->name);
  snprintf(tbuff, sizeof tbuff, "%s", inet_ntoa(ipcp->my_ip));
  log_Printf(LogIPCP, "myaddr %s hisaddr = %s\n",
             tbuff, inet_ntoa(ipcp->peer_ip));

  if (ipcp->peer_compproto >> 16 == PROTO_VJCOMP)
    sl_compress_init(&ipcp->vj.cslc, (ipcp->peer_compproto >> 8) & 255);

  if (!ipcp_InterfaceUp(ipcp))
    return 0;

#ifndef NORADIUS
  radius_Account_Set_Ip(&fp->bundle->radacct, &ipcp->peer_ip, &ipcp->ifmask);
  radius_Account(&fp->bundle->radius, &fp->bundle->radacct, fp->bundle->links,
                 RAD_START, &ipcp->throughput);

  if (*fp->bundle->radius.cfg.file && fp->bundle->radius.filterid)
    system_Select(fp->bundle, fp->bundle->radius.filterid, LINKUPFILE,
                  NULL, NULL);
  radius_StartTimer(fp->bundle);
#endif

  /*
   * XXX this stuff should really live in the FSM.  Our config should
   * associate executable sections in files with events.
   */
  if (system_Select(fp->bundle, tbuff, LINKUPFILE, NULL, NULL) < 0) {
    if (bundle_GetLabel(fp->bundle)) {
      if (system_Select(fp->bundle, bundle_GetLabel(fp->bundle),
                       LINKUPFILE, NULL, NULL) < 0)
        system_Select(fp->bundle, "MYADDR", LINKUPFILE, NULL, NULL);
    } else
      system_Select(fp->bundle, "MYADDR", LINKUPFILE, NULL, NULL);
  }

  fp->more.reqs = fp->more.naks = fp->more.rejs = ipcp->cfg.fsm.maxreq * 3;
  log_DisplayPrompts();

  return 1;
}
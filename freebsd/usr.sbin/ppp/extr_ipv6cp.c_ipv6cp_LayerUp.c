#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int maxreq; } ;
struct TYPE_14__ {TYPE_4__ fsm; } ;
struct ipv6cp {TYPE_5__ cfg; int /*<<< orphan*/  throughput; int /*<<< orphan*/  his_ifid; int /*<<< orphan*/  hisaddr; int /*<<< orphan*/  myaddr; } ;
struct TYPE_12__ {int reqs; int naks; int rejs; } ;
struct fsm {TYPE_3__ more; TYPE_6__* bundle; TYPE_1__* link; } ;
struct TYPE_11__ {scalar_t__* file; } ;
struct TYPE_16__ {char* filterid; TYPE_2__ cfg; } ;
struct TYPE_15__ {TYPE_7__ radius; int /*<<< orphan*/  links; int /*<<< orphan*/  radacct6; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Enabled (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINKUPFILE ; 
 int /*<<< orphan*/  LogIPV6CP ; 
 int NCP_ASCIIBUFFERSIZE ; 
 int /*<<< orphan*/  OPT_IPCP ; 
 int /*<<< orphan*/  RAD_START ; 
 char* bundle_GetLabel (TYPE_6__*) ; 
 struct ipv6cp* fsm2ipv6cp (struct fsm*) ; 
 int /*<<< orphan*/  ipv6cp_InterfaceUp (struct ipv6cp*) ; 
 int /*<<< orphan*/  log_DisplayPrompts () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* ncpaddr_ntoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_Account (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_Account_Set_Ipv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ system_Select (TYPE_6__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipv6cp_LayerUp(struct fsm *fp)
{
  /* We're now up */
  struct ipv6cp *ipv6cp = fsm2ipv6cp(fp);
  char tbuff[NCP_ASCIIBUFFERSIZE];

  log_Printf(LogIPV6CP, "%s: LayerUp.\n", fp->link->name);
  if (!ipv6cp_InterfaceUp(ipv6cp))
    return 0;

  snprintf(tbuff, sizeof tbuff, "%s", ncpaddr_ntoa(&ipv6cp->myaddr));
  log_Printf(LogIPV6CP, "myaddr %s hisaddr = %s\n",
             tbuff, ncpaddr_ntoa(&ipv6cp->hisaddr));

#ifndef NORADIUS
  radius_Account_Set_Ipv6(&fp->bundle->radacct6, ipv6cp->his_ifid);
  radius_Account(&fp->bundle->radius, &fp->bundle->radacct6,
		 fp->bundle->links, RAD_START, &ipv6cp->throughput);

  /*
   * XXX: Avoid duplicate evaluation of filterid between IPCP and
   * IPV6CP.  When IPCP is enabled and rejected, filterid is not
   * evaluated.
   */
  if (!Enabled(fp->bundle, OPT_IPCP)) {
    if (*fp->bundle->radius.cfg.file && fp->bundle->radius.filterid)
      system_Select(fp->bundle, fp->bundle->radius.filterid, LINKUPFILE,
		    NULL, NULL);
  }
#endif

  /*
   * XXX this stuff should really live in the FSM.  Our config should
   * associate executable sections in files with events.
   */
  if (system_Select(fp->bundle, tbuff, LINKUPFILE, NULL, NULL) < 0) {
    /*
     * XXX: Avoid duplicate evaluation of label between IPCP and
     * IPV6CP.  When IPCP is enabled and rejected, label is not
     * evaluated.
     */
    if (bundle_GetLabel(fp->bundle) && !Enabled(fp->bundle, OPT_IPCP)) {
      if (system_Select(fp->bundle, bundle_GetLabel(fp->bundle),
			LINKUPFILE, NULL, NULL) < 0)
	system_Select(fp->bundle, "MYADDR6", LINKUPFILE, NULL, NULL);
    } else
      system_Select(fp->bundle, "MYADDR6", LINKUPFILE, NULL, NULL);
  }

  fp->more.reqs = fp->more.naks = fp->more.rejs = ipv6cp->cfg.fsm.maxreq * 3;
  log_DisplayPrompts();

  return 1;
}
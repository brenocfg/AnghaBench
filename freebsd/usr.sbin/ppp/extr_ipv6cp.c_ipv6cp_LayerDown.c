#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ipv6cp {int /*<<< orphan*/  throughput; int /*<<< orphan*/  myaddr; } ;
struct fsm {TYPE_3__* bundle; TYPE_1__* link; } ;
struct TYPE_9__ {scalar_t__* file; } ;
struct TYPE_11__ {char* filterid; TYPE_2__ cfg; } ;
struct TYPE_10__ {TYPE_4__ radius; int /*<<< orphan*/  links; int /*<<< orphan*/  radacct6; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Enabled (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINKDOWNFILE ; 
 int /*<<< orphan*/  LogIPV6CP ; 
 int NCP_ASCIIBUFFERSIZE ; 
 int /*<<< orphan*/  OPT_IPCP ; 
 int /*<<< orphan*/  RAD_STOP ; 
 char* bundle_GetLabel (TYPE_3__*) ; 
 struct ipv6cp* fsm2ipv6cp (struct fsm*) ; 
 int /*<<< orphan*/  ipv6cp_Setup (struct ipv6cp*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char* ncpaddr_ntoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_Account (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_Flush (TYPE_4__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ system_Select (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipv6cp_LayerDown(struct fsm *fp)
{
  /* About to come down */
  struct ipv6cp *ipv6cp = fsm2ipv6cp(fp);
  static int recursing;
  char addr[NCP_ASCIIBUFFERSIZE];

  if (!recursing++) {
    snprintf(addr, sizeof addr, "%s", ncpaddr_ntoa(&ipv6cp->myaddr));
    log_Printf(LogIPV6CP, "%s: LayerDown: %s\n", fp->link->name, addr);

#ifndef NORADIUS
    radius_Flush(&fp->bundle->radius);
    radius_Account(&fp->bundle->radius, &fp->bundle->radacct6,
		   fp->bundle->links, RAD_STOP, &ipv6cp->throughput);

    /*
     * XXX: Avoid duplicate evaluation of filterid between IPCP and
     * IPV6CP.  When IPCP is enabled and rejected, filterid is not
     * evaluated.
     */
    if (!Enabled(fp->bundle, OPT_IPCP)) {
      if (*fp->bundle->radius.cfg.file && fp->bundle->radius.filterid)
	system_Select(fp->bundle, fp->bundle->radius.filterid, LINKDOWNFILE,
		      NULL, NULL);
    }
#endif

    /*
     * XXX this stuff should really live in the FSM.  Our config should
     * associate executable sections in files with events.
     */
    if (system_Select(fp->bundle, addr, LINKDOWNFILE, NULL, NULL) < 0) {
      /*
       * XXX: Avoid duplicate evaluation of label between IPCP and
       * IPV6CP.  When IPCP is enabled and rejected, label is not
       * evaluated.
       */
      if (bundle_GetLabel(fp->bundle) && !Enabled(fp->bundle, OPT_IPCP)) {
	if (system_Select(fp->bundle, bundle_GetLabel(fp->bundle),
			  LINKDOWNFILE, NULL, NULL) < 0)
	  system_Select(fp->bundle, "MYADDR6", LINKDOWNFILE, NULL, NULL);
      } else
	system_Select(fp->bundle, "MYADDR6", LINKDOWNFILE, NULL, NULL);
    }

    ipv6cp_Setup(ipv6cp);
  }
  recursing--;
}
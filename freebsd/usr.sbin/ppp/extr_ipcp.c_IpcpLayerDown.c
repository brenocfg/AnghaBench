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
struct ipcp {int /*<<< orphan*/  throughput; int /*<<< orphan*/  my_ip; } ;
struct fsm {TYPE_3__* bundle; TYPE_1__* link; } ;
struct TYPE_9__ {scalar_t__* file; } ;
struct TYPE_11__ {char* filterid; TYPE_2__ cfg; } ;
struct TYPE_10__ {TYPE_4__ radius; int /*<<< orphan*/  links; int /*<<< orphan*/  radacct; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  LINKDOWNFILE ; 
 int /*<<< orphan*/  LogIPCP ; 
 int /*<<< orphan*/  RAD_STOP ; 
 char* bundle_GetLabel (TYPE_3__*) ; 
 struct ipcp* fsm2ipcp (struct fsm*) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_Setup (struct ipcp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  radius_Account (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_Flush (TYPE_4__*) ; 
 int /*<<< orphan*/  radius_StopTimer (TYPE_4__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ system_Select (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
IpcpLayerDown(struct fsm *fp)
{
  /* About to come down */
  struct ipcp *ipcp = fsm2ipcp(fp);
  static int recursing;
  char addr[16];

  if (!recursing++) {
    snprintf(addr, sizeof addr, "%s", inet_ntoa(ipcp->my_ip));
    log_Printf(LogIPCP, "%s: LayerDown: %s\n", fp->link->name, addr);

#ifndef NORADIUS
    radius_Flush(&fp->bundle->radius);
    radius_Account(&fp->bundle->radius, &fp->bundle->radacct,
                   fp->bundle->links, RAD_STOP, &ipcp->throughput);

    if (*fp->bundle->radius.cfg.file && fp->bundle->radius.filterid)
      system_Select(fp->bundle, fp->bundle->radius.filterid, LINKDOWNFILE,
                    NULL, NULL);
    radius_StopTimer(&fp->bundle->radius);
#endif

    /*
     * XXX this stuff should really live in the FSM.  Our config should
     * associate executable sections in files with events.
     */
    if (system_Select(fp->bundle, addr, LINKDOWNFILE, NULL, NULL) < 0) {
      if (bundle_GetLabel(fp->bundle)) {
         if (system_Select(fp->bundle, bundle_GetLabel(fp->bundle),
                          LINKDOWNFILE, NULL, NULL) < 0)
         system_Select(fp->bundle, "MYADDR", LINKDOWNFILE, NULL, NULL);
      } else
        system_Select(fp->bundle, "MYADDR", LINKDOWNFILE, NULL, NULL);
    }

    ipcp_Setup(ipcp, INADDR_NONE);
  }
  recursing--;
}
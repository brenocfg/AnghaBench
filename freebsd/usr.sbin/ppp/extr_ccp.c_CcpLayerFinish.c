#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fsm {TYPE_3__* link; } ;
struct ccp_opt {struct ccp_opt* next; } ;
struct TYPE_5__ {struct ccp_opt* opt; } ;
struct ccp {TYPE_1__ out; } ;
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_6__ {TYPE_4__ fsm; } ;
struct TYPE_7__ {TYPE_2__ lcp; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 int /*<<< orphan*/  LogLCP ; 
 scalar_t__ ST_OPENED ; 
 scalar_t__ ccp_Required (struct ccp*) ; 
 int /*<<< orphan*/  free (struct ccp_opt*) ; 
 struct ccp* fsm2ccp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Close (TYPE_4__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CcpLayerFinish(struct fsm *fp)
{
  /* We're now down */
  struct ccp *ccp = fsm2ccp(fp);
  struct ccp_opt *next;

  log_Printf(LogCCP, "%s: LayerFinish.\n", fp->link->name);

  /*
   * Nuke options that may be left over from sending a REQ but never
   * coming up.
   */
  while (ccp->out.opt) {
    next = ccp->out.opt->next;
    free(ccp->out.opt);
    ccp->out.opt = next;
  }

  if (ccp_Required(ccp)) {
    if (fp->link->lcp.fsm.state == ST_OPENED)
      log_Printf(LogLCP, "%s: Closing due to CCP completion\n", fp->link->name);
    fsm_Close(&fp->link->lcp.fsm);
  }
}
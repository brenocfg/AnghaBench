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
struct TYPE_6__ {int reqs; int naks; int rejs; } ;
struct fsm {TYPE_2__ more; TYPE_1__* link; } ;
struct TYPE_7__ {int maxreq; } ;
struct TYPE_8__ {TYPE_3__ fsm; } ;
struct ccp {TYPE_4__ cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 struct ccp* fsm2ccp (struct fsm*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CcpLayerStart(struct fsm *fp)
{
  /* We're about to start up ! */
  struct ccp *ccp = fsm2ccp(fp);

  log_Printf(LogCCP, "%s: LayerStart.\n", fp->link->name);
  fp->more.reqs = fp->more.naks = fp->more.rejs = ccp->cfg.fsm.maxreq * 3;
}
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
struct TYPE_5__ {int maxreq; } ;
struct TYPE_6__ {TYPE_1__ fsm; } ;
struct lcp {scalar_t__ mru_req; TYPE_2__ cfg; scalar_t__ LcpFailedMagic; } ;
struct TYPE_8__ {int reqs; int naks; int rejs; } ;
struct fsm {TYPE_4__ more; TYPE_3__* link; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogLCP ; 
 struct lcp* fsm2lcp (struct fsm*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LcpLayerStart(struct fsm *fp)
{
  /* We're about to start up ! */
  struct lcp *lcp = fsm2lcp(fp);

  log_Printf(LogLCP, "%s: LayerStart\n", fp->link->name);
  lcp->LcpFailedMagic = 0;
  fp->more.reqs = fp->more.naks = fp->more.rejs = lcp->cfg.fsm.maxreq * 3;
  lcp->mru_req = 0;
}
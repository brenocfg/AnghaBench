#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct physical {int /*<<< orphan*/  hdlc; } ;
struct fsm {TYPE_1__* link; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogLCP ; 
 int /*<<< orphan*/  fsm2lcp (struct fsm*) ; 
 int /*<<< orphan*/  hdlc_StopTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcp_Setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct physical* link2physical (TYPE_1__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lqr_StopTimer (struct physical*) ; 

__attribute__((used)) static void
LcpLayerDown(struct fsm *fp)
{
  /* About to come down */
  struct physical *p = link2physical(fp->link);

  log_Printf(LogLCP, "%s: LayerDown\n", fp->link->name);
  hdlc_StopTimer(&p->hdlc);
  lqr_StopTimer(p);
  lcp_Setup(fsm2lcp(fp), 0);
}
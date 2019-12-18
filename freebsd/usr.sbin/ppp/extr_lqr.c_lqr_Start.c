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
struct TYPE_6__ {scalar_t__ load; } ;
struct TYPE_7__ {TYPE_2__ timer; } ;
struct TYPE_8__ {TYPE_3__ lqm; } ;
struct physical {TYPE_4__ hdlc; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct lcp {TYPE_1__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SendLqrReport (struct lcp*) ; 
 struct physical* link2physical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lqr_Setup (struct lcp*) ; 

void
lqr_Start(struct lcp *lcp)
{
  struct physical *p = link2physical(lcp->fsm.link);

  lqr_Setup(lcp);
  if (p->hdlc.lqm.timer.load)
    SendLqrReport(lcp);
}
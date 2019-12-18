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
struct TYPE_8__ {void* name; } ;
struct TYPE_6__ {void* name; } ;
struct TYPE_5__ {void* name; } ;
struct TYPE_7__ {TYPE_4__ StoppedTimer; TYPE_2__ OpenTimer; TYPE_1__ FsmTimer; int /*<<< orphan*/ * fn; } ;
struct lcp {TYPE_3__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcp_Callbacks ; 
 void** lcp_TimerNames ; 

void
lcp_SetupCallbacks(struct lcp *lcp)
{
  lcp->fsm.fn = &lcp_Callbacks;
  lcp->fsm.FsmTimer.name = lcp_TimerNames[0];
  lcp->fsm.OpenTimer.name = lcp_TimerNames[1];
  lcp->fsm.StoppedTimer.name = lcp_TimerNames[2];
}
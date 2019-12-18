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
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int /*<<< orphan*/  prompt; TYPE_9__* cx; } ;
struct TYPE_18__ {TYPE_8__* physical; } ;
struct TYPE_13__ {int load; } ;
struct TYPE_14__ {TYPE_4__ StoppedTimer; } ;
struct TYPE_15__ {TYPE_5__ fsm; } ;
struct TYPE_10__ {int load; } ;
struct TYPE_11__ {TYPE_1__ StoppedTimer; } ;
struct TYPE_12__ {TYPE_2__ fsm; } ;
struct TYPE_16__ {TYPE_6__ ccp; TYPE_3__ lcp; } ;
struct TYPE_17__ {TYPE_7__ link; } ;

/* Variables and functions */
 int SECTICKS ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
ShowStopped(struct cmdargs const *arg)
{
  prompt_Printf(arg->prompt, " Stopped Timer:  LCP: ");
  if (!arg->cx->physical->link.lcp.fsm.StoppedTimer.load)
    prompt_Printf(arg->prompt, "Disabled");
  else
    prompt_Printf(arg->prompt, "%ld secs",
                  arg->cx->physical->link.lcp.fsm.StoppedTimer.load / SECTICKS);

  prompt_Printf(arg->prompt, ", CCP: ");
  if (!arg->cx->physical->link.ccp.fsm.StoppedTimer.load)
    prompt_Printf(arg->prompt, "Disabled");
  else
    prompt_Printf(arg->prompt, "%ld secs",
                  arg->cx->physical->link.ccp.fsm.StoppedTimer.load / SECTICKS);

  prompt_Printf(arg->prompt, "\n");

  return 0;
}
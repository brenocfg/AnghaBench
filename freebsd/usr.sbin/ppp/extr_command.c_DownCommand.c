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
struct fsm {int dummy; } ;
struct cmdargs {int argc; int argn; TYPE_9__* bundle; TYPE_8__* cx; int /*<<< orphan*/ * argv; } ;
struct TYPE_13__ {struct fsm fsm; } ;
struct TYPE_14__ {TYPE_4__ ccp; } ;
struct TYPE_15__ {TYPE_5__ link; } ;
struct TYPE_16__ {TYPE_6__ mp; } ;
struct TYPE_18__ {TYPE_7__ ncp; } ;
struct TYPE_17__ {TYPE_3__* physical; } ;
struct TYPE_10__ {struct fsm fsm; } ;
struct TYPE_11__ {TYPE_1__ ccp; } ;
struct TYPE_12__ {TYPE_2__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_LCP ; 
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 int /*<<< orphan*/  bundle_Down (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datalink_Down (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm2initial (struct fsm*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
DownCommand(struct cmdargs const *arg)
{
  if (arg->argc == arg->argn) {
      if (arg->cx)
        datalink_Down(arg->cx, CLOSE_STAYDOWN);
      else
        bundle_Down(arg->bundle, CLOSE_STAYDOWN);
  } else if (arg->argc == arg->argn + 1) {
    if (!strcasecmp(arg->argv[arg->argn], "lcp")) {
      if (arg->cx)
        datalink_Down(arg->cx, CLOSE_LCP);
      else
        bundle_Down(arg->bundle, CLOSE_LCP);
    } else if (!strcasecmp(arg->argv[arg->argn], "ccp")) {
      struct fsm *fp = arg->cx ? &arg->cx->physical->link.ccp.fsm :
                                 &arg->bundle->ncp.mp.link.ccp.fsm;
      fsm2initial(fp);
    } else
      return -1;
  } else
    return -1;

  return 0;
}
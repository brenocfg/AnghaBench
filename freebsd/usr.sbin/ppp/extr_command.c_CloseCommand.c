#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fsm {scalar_t__ state; scalar_t__ open_mode; } ;
struct cmdargs {int argc; int argn; char** argv; TYPE_1__* cx; int /*<<< orphan*/  bundle; } ;
struct TYPE_5__ {struct fsm fsm; } ;
struct TYPE_6__ {TYPE_2__ ccp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_LCP ; 
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 scalar_t__ OPEN_PASSIVE ; 
 scalar_t__ ST_OPENED ; 
 int /*<<< orphan*/  bundle_Close (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* command_ChooseLink (struct cmdargs const*) ; 
 int /*<<< orphan*/  fsm_Close (struct fsm*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int
CloseCommand(struct cmdargs const *arg)
{
  if (arg->argc == arg->argn)
    bundle_Close(arg->bundle, arg->cx ? arg->cx->name : NULL, CLOSE_STAYDOWN);
  else if (arg->argc == arg->argn + 1) {
    if (!strcasecmp(arg->argv[arg->argn], "lcp"))
      bundle_Close(arg->bundle, arg->cx ? arg->cx->name : NULL, CLOSE_LCP);
    else if (!strcasecmp(arg->argv[arg->argn], "ccp") ||
             !strcasecmp(arg->argv[arg->argn], "ccp!")) {
      struct fsm *fp;

      fp = &command_ChooseLink(arg)->ccp.fsm;
      if (fp->state == ST_OPENED) {
        fsm_Close(fp);
        if (arg->argv[arg->argn][3] == '!')
          fp->open_mode = 0;		/* Stay ST_CLOSED */
        else
          fp->open_mode = OPEN_PASSIVE;	/* Wait for the peer to start */
      }
    } else
      return -1;
  } else
    return -1;

  return 0;
}
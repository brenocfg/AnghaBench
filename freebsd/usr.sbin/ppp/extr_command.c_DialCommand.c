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
struct cmdargs {scalar_t__ argc; scalar_t__ argn; TYPE_2__* cx; TYPE_4__* bundle; } ;
struct TYPE_5__ {int all; } ;
struct TYPE_8__ {TYPE_1__ phys_type; } ;
struct TYPE_7__ {int type; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; TYPE_3__* physical; } ;

/* Variables and functions */
 int LoadCommand (struct cmdargs const*) ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  PHYS_ALL ; 
 int PHYS_AUTO ; 
 int PHYS_INTERACTIVE ; 
 int /*<<< orphan*/  bundle_Open (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
DialCommand(struct cmdargs const *arg)
{
  int res;

  if ((arg->cx && !(arg->cx->physical->type & (PHYS_INTERACTIVE|PHYS_AUTO)))
      || (!arg->cx &&
          (arg->bundle->phys_type.all & ~(PHYS_INTERACTIVE|PHYS_AUTO)))) {
    log_Printf(LogWARN, "Manual dial is only available for auto and"
              " interactive links\n");
    return 1;
  }

  if (arg->argc > arg->argn && (res = LoadCommand(arg)) != 0)
    return res;

  bundle_Open(arg->bundle, arg->cx ? arg->cx->name : NULL, PHYS_ALL, 1);

  return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct filter {int /*<<< orphan*/  rule; } ;
struct cmdargs {int argc; int argn; int /*<<< orphan*/ * argv; TYPE_2__* bundle; } ;
struct TYPE_3__ {struct filter alive; struct filter dial; struct filter out; struct filter in; } ;
struct TYPE_4__ {int /*<<< orphan*/  ncp; TYPE_1__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  filter_Parse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int
filter_Set(struct cmdargs const *arg)
{
  struct filter *filter;

  if (arg->argc < arg->argn+2)
    return -1;

  if (!strcmp(arg->argv[arg->argn], "in"))
    filter = &arg->bundle->filter.in;
  else if (!strcmp(arg->argv[arg->argn], "out"))
    filter = &arg->bundle->filter.out;
  else if (!strcmp(arg->argv[arg->argn], "dial"))
    filter = &arg->bundle->filter.dial;
  else if (!strcmp(arg->argv[arg->argn], "alive"))
    filter = &arg->bundle->filter.alive;
  else {
    log_Printf(LogWARN, "filter_Set: %s: Invalid filter name.\n",
              arg->argv[arg->argn]);
    return -1;
  }

  filter_Parse(&arg->bundle->ncp, arg->argc - arg->argn - 1,
        arg->argv + arg->argn + 1, filter->rule);
  return 0;
}
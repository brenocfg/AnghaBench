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
struct cmdargs {int argc; int argn; char** argv; TYPE_3__* prompt; } ;
struct TYPE_6__ {int /*<<< orphan*/  auth; TYPE_2__* owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  passwd; } ;
struct TYPE_5__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_AUTH ; 
 int /*<<< orphan*/  LOCAL_NO_AUTH ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int
PasswdCommand(struct cmdargs const *arg)
{
  const char *pass;

  if (!arg->prompt) {
    log_Printf(LogWARN, "passwd: Cannot specify without a prompt\n");
    return 0;
  }

  if (arg->prompt->owner == NULL) {
    log_Printf(LogWARN, "passwd: Not required\n");
    return 0;
  }

  if (arg->argc == arg->argn)
    pass = "";
  else if (arg->argc > arg->argn+1)
    return -1;
  else
    pass = arg->argv[arg->argn];

  if (!strcmp(arg->prompt->owner->cfg.passwd, pass))
    arg->prompt->auth = LOCAL_AUTH;
  else
    arg->prompt->auth = LOCAL_NO_AUTH;

  return 0;
}
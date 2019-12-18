#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cmdargs {scalar_t__ argc; scalar_t__ argn; int /*<<< orphan*/  prompt; int /*<<< orphan*/  cx; int /*<<< orphan*/  argv; int /*<<< orphan*/  bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  FindExec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  ShowCommands ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ShowCommand(struct cmdargs const *arg)
{
  if (!arg->prompt)
    log_Printf(LogWARN, "show: Cannot show without a prompt\n");
  else if (arg->argc > arg->argn)
    FindExec(arg->bundle, ShowCommands, arg->argc, arg->argn, arg->argv,
             arg->prompt, arg->cx);
  else
    prompt_Printf(arg->prompt, "Use ``show ?'' to get a list.\n");

  return 0;
}
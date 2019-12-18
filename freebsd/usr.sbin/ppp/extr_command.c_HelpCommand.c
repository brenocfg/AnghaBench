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
struct cmdtab {char* name; char* alias; int lauth; char* helpmes; scalar_t__ func; int /*<<< orphan*/  syntax; } ;
struct cmdargs {size_t argc; size_t argn; TYPE_1__* prompt; struct cmdtab* cmdtab; int /*<<< orphan*/ * argv; } ;
struct TYPE_2__ {int auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prompt_Printf (TYPE_1__*,char*,...) ; 
 char* showcx (struct cmdtab const*) ; 
 int /*<<< orphan*/  strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
HelpCommand(struct cmdargs const *arg)
{
  struct cmdtab const *cmd;
  int n, cmax, dmax, cols, cxlen;
  const char *cx;

  if (!arg->prompt) {
    log_Printf(LogWARN, "help: Cannot help without a prompt\n");
    return 0;
  }

  if (arg->argc > arg->argn) {
    for (cmd = arg->cmdtab; cmd->name || cmd->alias; cmd++)
      if ((cmd->lauth & arg->prompt->auth) &&
          ((cmd->name && !strcasecmp(cmd->name, arg->argv[arg->argn])) ||
           (cmd->alias && !strcasecmp(cmd->alias, arg->argv[arg->argn])))) {
	prompt_Printf(arg->prompt, "%s %s\n", cmd->syntax, showcx(cmd));
	return 0;
      }
    return -1;
  }

  cmax = dmax = 0;
  for (cmd = arg->cmdtab; cmd->func; cmd++)
    if (cmd->name && (cmd->lauth & arg->prompt->auth)) {
      if ((n = strlen(cmd->name) + strlen(showcx(cmd))) > cmax)
        cmax = n;
      if ((n = strlen(cmd->helpmes)) > dmax)
        dmax = n;
    }

  cols = 80 / (dmax + cmax + 3);
  n = 0;
  prompt_Printf(arg->prompt, "(o) = Optional context,"
                " (c) = Context required\n");
  for (cmd = arg->cmdtab; cmd->func; cmd++)
    if (cmd->name && (cmd->lauth & arg->prompt->auth)) {
      cx = showcx(cmd);
      cxlen = cmax - strlen(cmd->name);
      if (n % cols != 0)
        prompt_Printf(arg->prompt, " ");
      prompt_Printf(arg->prompt, "%s%-*.*s: %-*.*s",
              cmd->name, cxlen, cxlen, cx, dmax, dmax, cmd->helpmes);
      if (++n % cols == 0)
        prompt_Printf(arg->prompt, "\n");
    }
  if (n % cols != 0)
    prompt_Printf(arg->prompt, "\n");

  return 0;
}
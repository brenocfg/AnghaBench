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
struct prompt {int auth; } ;
struct datalink {int name; } ;
struct cmdtab {int lauth; int (* func ) (struct cmdargs*) ;int /*<<< orphan*/  syntax; } ;
struct cmdargs {int argc; int argn; char const* const* argv; struct prompt* prompt; struct datalink* cx; struct bundle* bundle; struct cmdtab const* cmd; struct cmdtab const* cmdtab; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 struct cmdtab* FindCommand (struct cmdtab const*,char const* const,int*) ; 
 int LOCAL_CX ; 
 int LOCAL_CX_OPT ; 
 int /*<<< orphan*/  LogWARN ; 
 struct datalink* bundle2datalink (struct bundle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mkPrefix (int,char const* const*,char*,int) ; 
 int stub1 (struct cmdargs*) ; 

__attribute__((used)) static int
FindExec(struct bundle *bundle, struct cmdtab const *cmds, int argc, int argn,
         char const *const *argv, struct prompt *prompt, struct datalink *cx)
{
  struct cmdtab const *cmd;
  int val = 1;
  int nmatch;
  struct cmdargs arg;
  char prefix[100];

  cmd = FindCommand(cmds, argv[argn], &nmatch);
  if (nmatch > 1)
    log_Printf(LogWARN, "%s: Ambiguous command\n",
              mkPrefix(argn+1, argv, prefix, sizeof prefix));
  else if (cmd && (!prompt || (cmd->lauth & prompt->auth))) {
    if ((cmd->lauth & LOCAL_CX) && !cx)
      /* We've got no context, but we require it */
      cx = bundle2datalink(bundle, NULL);

    if ((cmd->lauth & LOCAL_CX) && !cx)
      log_Printf(LogWARN, "%s: No context (use the `link' command)\n",
                mkPrefix(argn+1, argv, prefix, sizeof prefix));
    else {
      if (cx && !(cmd->lauth & (LOCAL_CX|LOCAL_CX_OPT))) {
        log_Printf(LogWARN, "%s: Redundant context (%s) ignored\n",
                  mkPrefix(argn+1, argv, prefix, sizeof prefix), cx->name);
        cx = NULL;
      }
      arg.cmdtab = cmds;
      arg.cmd = cmd;
      arg.argc = argc;
      arg.argn = argn+1;
      arg.argv = argv;
      arg.bundle = bundle;
      arg.cx = cx;
      arg.prompt = prompt;
      val = (*cmd->func) (&arg);
    }
  } else
    log_Printf(LogWARN, "%s: Invalid command\n",
              mkPrefix(argn+1, argv, prefix, sizeof prefix));

  if (val == -1)
    log_Printf(LogWARN, "usage: %s\n", cmd->syntax);
  else if (val)
    log_Printf(LogWARN, "%s: Failed %d\n",
              mkPrefix(argn+1, argv, prefix, sizeof prefix), val);

  return val;
}
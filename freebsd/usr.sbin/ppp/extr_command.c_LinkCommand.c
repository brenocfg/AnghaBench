#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct datalink {struct datalink* next; } ;
struct cmdargs {int argc; int argn; TYPE_1__* cmd; int /*<<< orphan*/  prompt; int /*<<< orphan*/ * argv; TYPE_2__* bundle; } ;
struct TYPE_5__ {struct datalink* links; } ;
struct TYPE_4__ {char* syntax; } ;

/* Variables and functions */
 int /*<<< orphan*/  Commands ; 
 int /*<<< orphan*/  FindExec (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct datalink*) ; 
 int LINE_LEN ; 
 int /*<<< orphan*/  LogWARN ; 
 struct datalink* bundle2datalink (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
LinkCommand(struct cmdargs const *arg)
{
  if (arg->argc > arg->argn+1) {
    char namelist[LINE_LEN];
    struct datalink *cx;
    char *name;
    int result = 0;

    if (!strcmp(arg->argv[arg->argn], "*")) {
      struct datalink *dl;

      cx = arg->bundle->links;
      while (cx) {
        /* Watch it, the command could be a ``remove'' */
        dl = cx->next;
        FindExec(arg->bundle, Commands, arg->argc, arg->argn+1, arg->argv,
                 arg->prompt, cx);
        for (cx = arg->bundle->links; cx; cx = cx->next)
          if (cx == dl)
            break;		/* Pointer's still valid ! */
      }
    } else {
      strncpy(namelist, arg->argv[arg->argn], sizeof namelist - 1);
      namelist[sizeof namelist - 1] = '\0';
      for(name = strtok(namelist, ", "); name; name = strtok(NULL,", "))
        if (!bundle2datalink(arg->bundle, name)) {
          log_Printf(LogWARN, "link: %s: Invalid link name\n", name);
          return 1;
        }

      strncpy(namelist, arg->argv[arg->argn], sizeof namelist - 1);
      namelist[sizeof namelist - 1] = '\0';
      for(name = strtok(namelist, ", "); name; name = strtok(NULL,", ")) {
        cx = bundle2datalink(arg->bundle, name);
        if (cx)
          FindExec(arg->bundle, Commands, arg->argc, arg->argn+1, arg->argv,
                   arg->prompt, cx);
        else {
          log_Printf(LogWARN, "link: %s: Invalidated link name !\n", name);
          result++;
        }
      }
    }
    return result;
  }

  log_Printf(LogWARN, "usage: %s\n", arg->cmd->syntax);
  return 2;
}
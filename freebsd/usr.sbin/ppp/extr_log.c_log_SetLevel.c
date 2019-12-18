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
struct cmdargs {int argc; int argn; char** argv; TYPE_1__* prompt; } ;
struct TYPE_2__ {int /*<<< orphan*/  logmask; } ;

/* Variables and functions */
 int LogMAX ; 
 int LogMIN ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  log_Discard (int) ; 
 int /*<<< orphan*/  log_DiscardAll () ; 
 int /*<<< orphan*/  log_DiscardAllLocal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_DiscardLocal (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Keep (int) ; 
 int /*<<< orphan*/  log_KeepLocal (int,int /*<<< orphan*/ *) ; 
 char* log_Name (int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

int
log_SetLevel(struct cmdargs const *arg)
{
  int i, res, argc, local;
  char const *const *argv, *argp;

  argc = arg->argc - arg->argn;
  argv = arg->argv + arg->argn;
  res = 0;

  if (argc == 0 || strcasecmp(argv[0], "local"))
    local = 0;
  else {
    if (arg->prompt == NULL) {
      log_Printf(LogWARN, "set log local: Only available on the"
                 " command line\n");
      return 1;
    }
    argc--;
    argv++;
    local = 1;
  }

  if (argc == 0 || (argv[0][0] != '+' && argv[0][0] != '-')) {
    if (local)
      log_DiscardAllLocal(&arg->prompt->logmask);
    else
      log_DiscardAll();
  }

  while (argc--) {
    argp = **argv == '+' || **argv == '-' ? *argv + 1 : *argv;
    /* Special case 'all' */
    if (strcasecmp(argp, "all") == 0) {
        if (**argv == '-') {
          if (local)
            for (i = LogMIN; i <= LogMAX; i++)
              log_DiscardLocal(i, &arg->prompt->logmask);
          else
            for (i = LogMIN; i <= LogMAX; i++)
              log_Discard(i);
        } else if (local)
          for (i = LogMIN; i <= LogMAX; i++)
            log_KeepLocal(i, &arg->prompt->logmask);
        else
          for (i = LogMIN; i <= LogMAX; i++)
            log_Keep(i);
        argv++;
        continue;
    }
    for (i = LogMIN; i <= LogMAX; i++)
      if (strcasecmp(argp, log_Name(i)) == 0) {
	if (**argv == '-') {
          if (local)
            log_DiscardLocal(i, &arg->prompt->logmask);
          else
	    log_Discard(i);
	} else if (local)
          log_KeepLocal(i, &arg->prompt->logmask);
        else
          log_Keep(i);
	break;
      }
    if (i > LogMAX) {
      log_Printf(LogWARN, "%s: Invalid log value\n", argp);
      res = -1;
    }
    argv++;
  }
  return res;
}
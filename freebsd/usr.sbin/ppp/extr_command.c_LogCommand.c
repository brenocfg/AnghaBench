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
struct cmdargs {int argn; int argc; int /*<<< orphan*/  bundle; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Concatinate (char*,int,int,char const* const*) ; 
 int LINE_LEN ; 
 int /*<<< orphan*/  LogLOG ; 
 int /*<<< orphan*/  LogWARN ; 
 int MAXARGS ; 
 int /*<<< orphan*/  command_Expand (char**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_Free (int,char**) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
LogCommand(struct cmdargs const *arg)
{
  char buf[LINE_LEN];

  if (arg->argn < arg->argc) {
    char *argv[MAXARGS];
    int argc = arg->argc - arg->argn;

    if (argc >= (int)(sizeof argv / sizeof argv[0])) {
      argc = sizeof argv / sizeof argv[0] - 1;
      log_Printf(LogWARN, "Truncating log command to %d args\n", argc);
    }
    command_Expand(argv, argc, arg->argv + arg->argn, arg->bundle, 1, getpid());
    Concatinate(buf, sizeof buf, argc, (const char *const *)argv);
    log_Printf(LogLOG, "%s\n", buf);
    command_Free(argc, argv);
    return 0;
  }

  return -1;
}
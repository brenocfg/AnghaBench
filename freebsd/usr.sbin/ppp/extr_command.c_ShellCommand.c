#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argc; int argn; char const** argv; TYPE_1__* prompt; int /*<<< orphan*/  bundle; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {int fd_out; scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  ID0realuid () ; 
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int MAXARGS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  command_Expand (char**,int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int daemon (int,int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execl (char const*,char const*,char*) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fork () ; 
 int getdtablesize () ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  prompt_TtyCommandMode (TYPE_1__*) ; 
 int /*<<< orphan*/  prompt_TtyOldMode (TYPE_1__*) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_TermService () ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ShellCommand(struct cmdargs const *arg, int bg)
{
  const char *shell;
  pid_t shpid, pid;

#ifdef SHELL_ONLY_INTERACTIVELY
  /* we're only allowed to shell when we run ppp interactively */
  if (arg->prompt && arg->prompt->owner) {
    log_Printf(LogWARN, "Can't start a shell from a network connection\n");
    return 1;
  }
#endif

  if (arg->argc == arg->argn) {
    if (!arg->prompt) {
      log_Printf(LogWARN, "Can't start an interactive shell from"
                " a config file\n");
      return 1;
    } else if (arg->prompt->owner) {
      log_Printf(LogWARN, "Can't start an interactive shell from"
                " a socket connection\n");
      return 1;
    } else if (bg) {
      log_Printf(LogWARN, "Can only start an interactive shell in"
		" the foreground mode\n");
      return 1;
    }
  }

  pid = getpid();
  if ((shpid = fork()) == 0) {
    int i, fd;

    if ((shell = getenv("SHELL")) == NULL)
      shell = _PATH_BSHELL;

    timer_TermService();

    if (arg->prompt)
      fd = arg->prompt->fd_out;
    else if ((fd = open(_PATH_DEVNULL, O_RDWR)) == -1) {
      log_Printf(LogALERT, "Failed to open %s: %s\n",
                _PATH_DEVNULL, strerror(errno));
      exit(1);
    }
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    for (i = getdtablesize(); i > STDERR_FILENO; i--)
      fcntl(i, F_SETFD, 1);

#ifndef NOSUID
    setuid(ID0realuid());
#endif
    if (arg->argc > arg->argn) {
      /* substitute pseudo args */
      char *argv[MAXARGS];
      int argc = arg->argc - arg->argn;

      if (argc >= (int)(sizeof argv / sizeof argv[0])) {
        argc = sizeof argv / sizeof argv[0] - 1;
        log_Printf(LogWARN, "Truncating shell command to %d args\n", argc);
      }
      command_Expand(argv, argc, arg->argv + arg->argn, arg->bundle, 0, pid);
      if (bg) {
	pid_t p;

	p = getpid();
	if (daemon(1, 1) == -1) {
	  log_Printf(LogERROR, "%ld: daemon: %s\n", (long)p, strerror(errno));
	  exit(1);
	}
      } else if (arg->prompt)
        printf("ppp: Pausing until %s finishes\n", arg->argv[arg->argn]);
      execvp(argv[0], argv);
    } else {
      if (arg->prompt)
        printf("ppp: Pausing until %s finishes\n", shell);
      prompt_TtyOldMode(arg->prompt);
      execl(shell, shell, (char *)NULL);
    }

    log_Printf(LogWARN, "exec() of %s failed: %s\n",
              arg->argc > arg->argn ? arg->argv[arg->argn] : shell,
              strerror(errno));
    _exit(255);
  }

  if (shpid == (pid_t)-1)
    log_Printf(LogERROR, "Fork failed: %s\n", strerror(errno));
  else {
    int status;
    waitpid(shpid, &status, 0);
  }

  if (arg->prompt && !arg->prompt->owner)
    prompt_TtyCommandMode(arg->prompt);

  return 0;
}
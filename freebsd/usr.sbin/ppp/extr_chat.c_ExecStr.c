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
struct physical {int fd; TYPE_1__* dl; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  ID0realuid () ; 
 int /*<<< orphan*/  LogCHAT ; 
 int /*<<< orphan*/  LogWARN ; 
 int MAXARGS ; 
 int MakeArgs (char*,char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PARSE_NOHASH ; 
 int PARSE_REDUCE ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  VECSIZE (char**) ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  command_Expand (char**,int,char const* const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dup (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getdtablesize () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_TermService () ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExecStr(struct physical *physical, char *command, char *out, int olen)
{
  pid_t pid;
  int fids[2];
  char *argv[MAXARGS], *vector[MAXARGS], *startout, *endout;
  int stat, nb, argc, i;

  log_Printf(LogCHAT, "Exec: %s\n", command);
  if ((argc = MakeArgs(command, vector, VECSIZE(vector),
                       PARSE_REDUCE|PARSE_NOHASH)) <= 0) {
    if (argc < 0)
      log_Printf(LogWARN, "Syntax error in exec command\n");
    *out = '\0';
    return;
  }

  if (pipe(fids) < 0) {
    log_Printf(LogCHAT, "Unable to create pipe in ExecStr: %s\n",
	      strerror(errno));
    *out = '\0';
    return;
  }
  if ((pid = fork()) == 0) {
    command_Expand(argv, argc, (char const *const *)vector,
                   physical->dl->bundle, 0, getpid());
    close(fids[0]);
    timer_TermService();
    if (fids[1] == STDIN_FILENO)
      fids[1] = dup(fids[1]);
    dup2(physical->fd, STDIN_FILENO);
    dup2(fids[1], STDERR_FILENO);
    dup2(STDIN_FILENO, STDOUT_FILENO);
    close(3);
    if (open(_PATH_TTY, O_RDWR) != 3)
      open(_PATH_DEVNULL, O_RDWR);	/* Leave it closed if it fails... */
    for (i = getdtablesize(); i > 3; i--)
      fcntl(i, F_SETFD, 1);
#ifndef NOSUID
    setuid(ID0realuid());
#endif
    execvp(argv[0], argv);
    fprintf(stderr, "execvp: %s: %s\n", argv[0], strerror(errno));
    _exit(127);
  } else {
    char *name = strdup(vector[0]);

    close(fids[1]);
    endout = out + olen - 1;
    startout = out;
    while (out < endout) {
      nb = read(fids[0], out, 1);
      if (nb <= 0)
	break;
      out++;
    }
    *out = '\0';
    close(fids[0]);
    close(fids[1]);
    waitpid(pid, &stat, WNOHANG);
    if (WIFSIGNALED(stat)) {
      log_Printf(LogWARN, "%s: signal %d\n", name, WTERMSIG(stat));
      free(name);
      *out = '\0';
      return;
    } else if (WIFEXITED(stat)) {
      switch (WEXITSTATUS(stat)) {
        case 0:
          free(name);
          break;
        case 127:
          log_Printf(LogWARN, "%s: %s\n", name, startout);
          free(name);
          *out = '\0';
          return;
          break;
        default:
          log_Printf(LogWARN, "%s: exit %d\n", name, WEXITSTATUS(stat));
          free(name);
          *out = '\0';
          return;
          break;
      }
    } else {
      log_Printf(LogWARN, "%s: Unexpected exit result\n", name);
      free(name);
      *out = '\0';
      return;
    }
  }
}
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
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pidfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pid_file (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
daemonize (void)
{
  pid_t pid, sid;
  int fd;

  /* Clone ourselves to make a child */
  pid = fork ();

  if (pid < 0)
    exit (EXIT_FAILURE);
  if (pid > 0) {
    write_pid_file (conf.pidfile, pid);
    printf ("Daemonized GoAccess: %d\n", pid);
    exit (EXIT_SUCCESS);
  }

  umask (0);
  /* attempt to create our own process group */
  sid = setsid ();
  if (sid < 0) {
    LOG_DEBUG (("Unable to setsid: %s.\n", strerror (errno)));
    exit (EXIT_FAILURE);
  }

  /* set the working directory to the root directory.
   * requires the user to specify absolute paths */
  if (chdir ("/") < 0) {
    LOG_DEBUG (("Unable to set chdir: %s.\n", strerror (errno)));
    exit (EXIT_FAILURE);
  }

  /* redirect fd's 0,1,2 to /dev/null */
  /* Note that the user will need to use --debug-file for log output */
  if ((fd = open ("/dev/null", O_RDWR, 0)) == -1) {
    LOG_DEBUG (("Unable to open /dev/null: %s.\n", strerror (errno)));
    exit (EXIT_FAILURE);
  }

  dup2 (fd, STDIN_FILENO);
  dup2 (fd, STDOUT_FILENO);
  dup2 (fd, STDERR_FILENO);
  if (fd > STDERR_FILENO) {
    close (fd);
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  real_time_html; scalar_t__ output_stdout; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pipe; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  add_dash_filename () ; 
 TYPE_2__ conf ; 
 int dup (scalar_t__) ; 
 int /*<<< orphan*/  dup2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ freopen (char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* glog ; 
 int open_term (char**) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_pipe_stdin (void)
{
  char *term = NULL;
  FILE *pipe = stdin;
  int fd1, fd2;

  /* If unable to open a terminal, yet data is being piped, then it's
   * probably from the cron.
   *
   * Note: If used from the cron, it will require the
   * user to use a single dash to parse piped data such as:
   * cat access.log | goaccess - */
  if ((fd1 = open_term (&term)) == -1)
    goto out;

  if ((fd2 = dup (fileno (stdin))) == -1)
    FATAL ("Unable to dup stdin: %s", strerror (errno));

  pipe = fdopen (fd2, "r");
  if (freopen (term, "r", stdin) == 0)
    FATAL ("Unable to open input from TTY");
  if (fileno (stdin) != 0)
    (void) dup2 (fileno (stdin), 0);

  add_dash_filename ();
  /* no need to set it as non-blocking since we are simply outputting a
   * static report */
  if (conf.output_stdout && !conf.real_time_html)
    goto out;

  /* Using select(), poll(), or epoll(), etc may be a better choice... */
  if (fcntl (fd2, F_SETFL, fcntl (fd2, F_GETFL, 0) | O_NONBLOCK) == -1)
    FATAL ("Unable to set fd as non-blocking: %s.", strerror (errno));
out:

  glog->pipe = pipe;
  free (term);
}
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

/* Variables and functions */
 scalar_t__ EINTR ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int child_pid ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

void check_child_status (void) {
  if (!child_pid) {
    return;
  }
  int status = 0;
  int res = waitpid (child_pid, &status, WNOHANG);
  if (res == child_pid) {
    if (WIFEXITED (status) || WIFSIGNALED (status)) {
      if (verbosity > 0) {
        fprintf (stderr, "child process %d terminated: exited = %d, signaled = %d, exit code = %d\n",
          child_pid, WIFEXITED (status) ? 1 : 0, WIFSIGNALED (status) ? 1 : 0, WEXITSTATUS (status));
      }
      child_pid = 0;
    }
  } else if (res == -1) {
    if (errno != EINTR) {
      fprintf (stderr, "waitpid (%d): %m\n", child_pid);
      child_pid = 0;
    }
  } else if (res) {
    fprintf (stderr, "waitpid (%d) returned %d???\n", child_pid, res);
  }
}
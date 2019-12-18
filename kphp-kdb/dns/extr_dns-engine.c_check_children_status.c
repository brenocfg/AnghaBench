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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  check_children_dead () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getppid () ; 
 int /*<<< orphan*/  kill_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,int,...) ; 
 int parent_pid ; 
 int* pids ; 
 scalar_t__ slave_mode ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int workers ; 

__attribute__((used)) static void check_children_status (void) {
  if (workers) {
    int i;
    for (i = 0; i < workers; i++) {
      int status = 0;
      int res = waitpid (pids[i], &status, WNOHANG);
      if (res == pids[i]) {
        if (WIFEXITED (status) || WIFSIGNALED (status)) {
          kprintf ("Child %d terminated, aborting\n", pids[i]);
          pids[i] = 0;
          kill_children (SIGTERM);
          check_children_dead ();
          exit (EXIT_FAILURE);
        }
      } else if (res == 0) {
      } else if (res != -1 || errno != EINTR) {
        kprintf ("Child %d: unknown result during wait (%d, %m), aborting\n", pids[i], res);
        pids[i] = 0;
        kill_children (SIGTERM);
        check_children_dead ();
        exit (EXIT_FAILURE);
      }
    }
  } else if (slave_mode) {
    if (getppid () != parent_pid) {
      kprintf ("Parent %d is changed to %d, aborting\n", parent_pid, getppid ());
      exit (EXIT_FAILURE);
    }
  }
}
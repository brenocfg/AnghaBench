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
 int /*<<< orphan*/  assert (int) ; 
 int child_pid ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sfd ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_stats () ; 

void fork_write_stats (void) {
  if (child_pid) {
    return;
  }

  int res = fork();

  if (res < 0) {
    fprintf (stderr, "fork: %m\n");
  } else if (!res) {
    assert (close (sfd) >= 0);

    write_stats();
    exit (0);
  } else {
    if (verbosity > 0) {
      fprintf (stderr, "created child process pid = %d\n", res);
    }
    child_pid = res;
  }
}
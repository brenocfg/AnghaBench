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
 int /*<<< orphan*/ * binlogname ; 
 int child_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flush_binlog_ts () ; 
 scalar_t__ force_write_index ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int save_index () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

void fork_write_index (void) {
  if (child_pid) {
    if (verbosity > 0) {
      fprintf (stderr, "process with pid %d already generates index, skipping\n", child_pid);
    }
    return;
  }

  flush_binlog_ts();

  int res = fork();

  if (res < 0) {
    fprintf (stderr, "fork: %m\n");
  } else if (!res) {
    binlogname = NULL;
    res = save_index();
    exit (res);
  } else {
    if (verbosity > 0) {
      fprintf (stderr, "created child process pid = %d\n", res);
    }
    child_pid = res;
  }

  force_write_index = 0;
}
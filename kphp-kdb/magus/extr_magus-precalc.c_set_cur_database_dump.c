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
 char* database_dump_prefix ; 
 int /*<<< orphan*/  dl_close_file (size_t) ; 
 int /*<<< orphan*/  dl_get_memory_used () ; 
 scalar_t__ dl_open_file (size_t,int /*<<< orphan*/ ,int) ; 
 size_t dump_fd ; 
 int /*<<< orphan*/  dump_name ; 
 int engine_n ; 
 int* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int set_cur_database_dump (int dump_id) {
  assert (0 <= dump_id && dump_id < engine_n && database_dump_prefix != NULL);

  if (fd[dump_fd] != -1) {
    dl_close_file (dump_fd);
  }

  int cur_dump = dump_id;

  if (verbosity > 0) {
    fprintf (stderr, "\nSwitching to database dump %d, memory_used = %lld\n", cur_dump, dl_get_memory_used());
  }

  snprintf (dump_name, 100, "%s%03d.dump", database_dump_prefix, cur_dump);
  return dl_open_file (dump_fd, dump_name, -1) >= 0;
}
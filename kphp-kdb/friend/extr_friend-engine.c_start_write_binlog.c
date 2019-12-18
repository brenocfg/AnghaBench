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

int start_write_binlog (void) {
  return -1; // temporary disabled

  /*if (binlog_disabled != 2 || !binlogname) {
    return -1;
  }
  if (!is_write_log_empty ()) {
    return -3;
  }
  if (lock_whole_file (fd[2], F_WRLCK) <= 0) {
    return -2;
  }
  if (verbosity > 0) {
    fprintf (stderr, "obtained write lock for binlog, start writing...\n");
  }
  read_new_events();

  clear_read_log();

  //set_log_data (fd[2], fsize[2]);

  epoll_pre_event = 0;

  binlog_disabled = 0;
  clear_write_log();
  return 1;*/
}
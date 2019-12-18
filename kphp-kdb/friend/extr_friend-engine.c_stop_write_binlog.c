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

int stop_write_binlog (void) {
  return -1; //temporary disabled

  /*if (!Binlog || binlog_disabled != 0 || !binlogname) {
    return -1;
  }
  flush_binlog_last();
  fsync (Binlog->fd);
  if (lock_whole_file (Binlog->fd, F_UNLCK) <= 0) {
    return -2;
  }
  if (verbosity > 0) {
    fprintf (stderr, "released write lock for binlog, start reading...\n");
  }

  clear_read_log();

  //set_log_data (fd[2], fsize[2]);

  epoll_pre_event = read_new_events;

  binlog_disabled = 2;
  clear_write_log();

  return 1;*/
}
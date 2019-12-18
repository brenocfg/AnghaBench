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
 int /*<<< orphan*/  LogBuffer ; 
 int /*<<< orphan*/  LogSlaveBuffer ; 
 int /*<<< orphan*/  SLOG_BUFFER_SIZE ; 
 int /*<<< orphan*/  ULOG_BUFFER_SIZE ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  aio_write_start ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_disabled ; 
 scalar_t__ binlog_write_active ; 
 int /*<<< orphan*/  clear_one_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flush_binlog () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usleep (int) ; 

void clear_write_log (void) {
  if (binlog_disabled) {
    clear_one_log (&W, LogSlaveBuffer, SLOG_BUFFER_SIZE);
  } else {
    /* wait for pending aio_write termination */
    int cnt = 0;
    while (binlog_write_active) {
      flush_binlog ();
      usleep (10000);
      if (++cnt > 300) {
        fprintf (stderr, "cannot write binlog for 3 seconds!");
        exit (3);
      }
    }
    if (cnt > 0) {
      fprintf (stderr, "clear_write_log: had to wait %d milliseconds for aio_write termination\n", cnt);
    }

    assert (!aio_write_start);

    clear_one_log (&W, LogBuffer, ULOG_BUFFER_SIZE);
  }
}
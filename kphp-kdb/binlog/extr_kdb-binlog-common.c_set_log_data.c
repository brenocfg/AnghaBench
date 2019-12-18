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
struct TYPE_2__ {int /*<<< orphan*/  log_start_pos; } ;

/* Variables and functions */
 scalar_t__ LogCopyBuffer ; 
 scalar_t__ ULOG_BUFFER_SIZE ; 
 TYPE_1__ W ; 
 scalar_t__ binlog_check_mode ; 
 int binlog_fd ; 
 long long binlog_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ load_binlog_headers (int) ; 
 int /*<<< orphan*/  log_pos ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

void set_log_data (int logfd, long long logsize) {
  binlog_fd = logfd;
  binlog_size = logsize;
  if (load_binlog_headers (logfd) < 0) {
    fprintf (stderr, "bad binlog headers (fd=%d)\n", logfd);
    exit (1);
  }
  if (binlog_check_mode && !LogCopyBuffer) {
    LogCopyBuffer = malloc (ULOG_BUFFER_SIZE + 16);
  }
  W.log_start_pos = log_pos;
}
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
 int binlog_fd ; 
 scalar_t__ binlog_size ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 

void clear_log (void) {
  clear_read_log ();
  clear_write_log ();
//  log_last_ts = 0;
//  log_pos = 0;
  binlog_fd = -1;
  binlog_size = 0;
}
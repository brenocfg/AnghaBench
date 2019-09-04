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
 int /*<<< orphan*/  alloc_log_crc32_event () ; 
 int /*<<< orphan*/  alloc_log_timestamp_event () ; 
 scalar_t__ binlog_disabled ; 
 int /*<<< orphan*/  binlogname ; 
 int disable_crc32 ; 
 int disable_ts ; 
 int /*<<< orphan*/  flush_binlog_forced (int) ; 
 scalar_t__ log_last_ts ; 

void flush_binlog_ts (void) {
  if (!binlogname || binlog_disabled) {
    return;
  }
  if (log_last_ts) {
    if (!(disable_crc32 & 1)) {
      alloc_log_crc32_event ();
    } else if (!(disable_ts & 1)) {
      alloc_log_timestamp_event ();
    }
  }
  flush_binlog_forced (1);
}
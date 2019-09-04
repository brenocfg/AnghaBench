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
 int /*<<< orphan*/  LE_TIMESTAMP_MAGIC ; 
 int /*<<< orphan*/  alloc_log_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_binlog () ; 
 scalar_t__ log_last_ts ; 

void flush_binlog_ts (void) {
  if (log_last_ts) {
    alloc_log_event (LE_TIMESTAMP_MAGIC, 0, 0, 0);
  }
  flush_binlog();
}
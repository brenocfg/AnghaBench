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
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_delay_queues () ; 

void cron (void) {
  flush_binlog_forced (0);
  scan_delay_queues ();
  flush_binlog_forced (0);
}
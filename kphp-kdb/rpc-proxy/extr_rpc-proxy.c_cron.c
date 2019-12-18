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
 scalar_t__ binlog_mode_on ; 
 int /*<<< orphan*/  dyn_garbage_collector () ; 
 int /*<<< orphan*/  flush_cbinlog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_index () ; 

void cron (void) {
  dyn_garbage_collector ();
  if (binlog_mode_on) {
    flush_cbinlog (0);
    write_index ();
  }
}
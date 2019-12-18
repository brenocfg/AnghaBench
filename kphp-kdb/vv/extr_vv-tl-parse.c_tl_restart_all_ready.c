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
 int /*<<< orphan*/  tl_aio_query_restart_all_finished () ; 
 int /*<<< orphan*/  tl_binlog_wait_restart_all_finished () ; 
 int /*<<< orphan*/  tl_binlog_wait_time_restart_all_finished () ; 

void tl_restart_all_ready (void) {
  tl_binlog_wait_time_restart_all_finished ();
  tl_binlog_wait_restart_all_finished ();
  tl_aio_query_restart_all_finished ();
}
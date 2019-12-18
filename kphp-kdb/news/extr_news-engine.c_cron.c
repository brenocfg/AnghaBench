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
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  dyn_garbage_collector () ; 
 int /*<<< orphan*/  flush_binlog () ; 
 int /*<<< orphan*/  last_collect_garbage_time ; 
 int /*<<< orphan*/  news_collect_garbage (int) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  update_offsets (int) ; 

void cron (void) {
  create_all_outbound_connections ();
  flush_binlog ();
  if (!binlog_disabled) {
    update_offsets (1);
  }
  dyn_garbage_collector ();
  last_collect_garbage_time = now;
  news_collect_garbage (100);
}
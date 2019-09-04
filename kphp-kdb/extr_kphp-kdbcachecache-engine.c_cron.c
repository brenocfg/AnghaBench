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
struct TYPE_2__ {scalar_t__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  binlog_disabled ; 
 scalar_t__ cache_acounters_update_step (int) ; 
 int /*<<< orphan*/  cache_garbage_collector_step (int) ; 
 int /*<<< orphan*/  cache_stats_relax () ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  cron_acounter_update_calls ; 
 int /*<<< orphan*/  dyn_garbage_collector () ; 
 int /*<<< orphan*/  flush_binlog () ; 
 TYPE_1__ get_top_access_stat ; 

__attribute__((used)) static void cron (void) {
  create_all_outbound_connections ();
  if (get_top_access_stat.t) {
    cron_acounter_update_calls += cache_acounters_update_step (500);
  }
  if (!binlog_disabled) {
    cache_garbage_collector_step (500);
  }
  flush_binlog ();
  dyn_garbage_collector ();
  cache_stats_relax ();
}
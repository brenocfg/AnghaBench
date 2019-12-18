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
 scalar_t__ MAX_COUNTERS_ALLOCATED ; 
 int /*<<< orphan*/  flush_view_counters () ; 
 scalar_t__ free_LRU () ; 
 int now ; 
 scalar_t__ tot_counters_allocated ; 

void cron (void) {
  static int last_viewcnt_flush = 0;
  if (now >= last_viewcnt_flush + 60) {
    flush_view_counters();
    last_viewcnt_flush = now - now % 60;
  }
  while (tot_counters_allocated >= MAX_COUNTERS_ALLOCATED && free_LRU()) {
  }
  //  check_all_aio_completions ();

  //flush_binlog();
}
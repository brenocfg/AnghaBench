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
 int /*<<< orphan*/  CLOCK_PROCESS_CPUTIME_ID ; 
 int STAT_CNT ; 
 size_t STAT_PERIOD ; 
 int /*<<< orphan*/  check_child_status () ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 scalar_t__ force_write_stats ; 
 int /*<<< orphan*/  fork_write_stats () ; 
 int /*<<< orphan*/  free_by_time (int) ; 
 int get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 size_t now ; 
 int** stats ; 
 int* stats_now ; 

void cron (void) {
  create_all_outbound_connections();

  free_by_time (137);

#ifdef HISTORY
  stats_now = stats[now % STAT_PERIOD];
  memset (stats_now, 0, STAT_CNT * sizeof (long long));
  stats_now[6] = get_utime (CLOCK_PROCESS_CPUTIME_ID) * 1e9;
#endif

  if (force_write_stats) {
    fork_write_stats();
    force_write_stats = 0;
  }
  check_child_status();
}
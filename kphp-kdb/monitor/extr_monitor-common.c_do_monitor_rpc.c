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
 int /*<<< orphan*/ * active_pids ; 
 int active_pnum ; 
 int /*<<< orphan*/  get_precise_time (int) ; 
 int /*<<< orphan*/  get_proc_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_check_time ; 
 scalar_t__ try_monitor_rpc (int /*<<< orphan*/ ) ; 

int do_monitor_rpc (void) {
  int cnt = 0, i;
  last_check_time = get_precise_time (1000000);
  for (i = 0; i < active_pnum; i++) {
    if (try_monitor_rpc (get_proc_status (active_pids[i])) > 0) {
      cnt++;
    }
  }
  return cnt;
}
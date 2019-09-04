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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  STATS_COUNT ; 
 int /*<<< orphan*/  STATS_INTERVAL ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  show_stats ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stats_left ; 
 int /*<<< orphan*/  timer_handle ; 
 int /*<<< orphan*/  uv_now (int /*<<< orphan*/ ) ; 
 int uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_stats_collection(void) {
  int r;

  /* Show-stats timer */
  stats_left = STATS_COUNT;
  r = uv_timer_init(loop, &timer_handle);
  ASSERT(r == 0);
  r = uv_timer_start(&timer_handle, show_stats, STATS_INTERVAL, STATS_INTERVAL);
  ASSERT(r == 0);

  uv_update_time(loop);
  start_time = uv_now(loop);
}
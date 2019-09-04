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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ timer_early_check_expected_time ; 
 int uv_hrtime () ; 

__attribute__((used)) static void timer_early_check_cb(uv_timer_t* handle) {
  uint64_t hrtime = uv_hrtime() / 1000000;
  ASSERT(hrtime >= timer_early_check_expected_time);
}
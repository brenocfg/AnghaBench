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
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int get_utime_monotonic () ; 
 int precise_now ; 
 long long precise_now_ticks ; 
 int /*<<< orphan*/  precise_now_updates ; 
 long long rdtsc () ; 

void update_precise_now () {
  long long x = rdtsc ();
  if (x - precise_now_ticks > 1000000) {
    ADD_CNT (precise_now_updates);
    precise_now_ticks = x;
    precise_now = get_utime_monotonic ();
  } else {
    precise_now += 1e-6;
  }
}
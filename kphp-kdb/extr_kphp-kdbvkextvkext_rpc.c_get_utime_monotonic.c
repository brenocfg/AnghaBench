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
struct timespec {double tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  END_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  utime ; 

__attribute__((used)) static double get_utime_monotonic (void) { /* {{{ */
  ADD_CNT (utime);
  START_TICKS (utime);
  struct timespec T;
  assert (clock_gettime(CLOCK_MONOTONIC, &T) >= 0);
  END_TICKS (utime);
  return T.tv_sec + (double) T.tv_nsec * 1e-9;
}
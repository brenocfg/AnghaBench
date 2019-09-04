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
struct timespec {double tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BOOTTIME ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ EINVAL ; 
 int UV__ERR (scalar_t__) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ errno ; 

int uv_uptime(double* uptime) {
  static volatile int no_clock_boottime;
  struct timespec now;
  int r;

  /* Try CLOCK_BOOTTIME first, fall back to CLOCK_MONOTONIC if not available
   * (pre-2.6.39 kernels). CLOCK_MONOTONIC doesn't increase when the system
   * is suspended.
   */
  if (no_clock_boottime) {
    retry: r = clock_gettime(CLOCK_MONOTONIC, &now);
  }
  else if ((r = clock_gettime(CLOCK_BOOTTIME, &now)) && errno == EINVAL) {
    no_clock_boottime = 1;
    goto retry;
  }

  if (r)
    return UV__ERR(errno);

  *uptime = now.tv_sec;
  return 0;
}
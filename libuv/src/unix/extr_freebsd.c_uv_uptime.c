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
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  errno ; 

int uv_uptime(double* uptime) {
  int r;
  struct timespec sp;
  r = clock_gettime(CLOCK_MONOTONIC, &sp);
  if (r)
    return UV__ERR(errno);

  *uptime = sp.tv_sec;
  return 0;
}
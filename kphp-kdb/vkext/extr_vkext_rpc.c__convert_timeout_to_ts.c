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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static struct timeval _convert_timeout_to_ts (double t) { /* {{{ */
  struct timeval tv;
  int secs = 0;

  secs = (int)t;
  tv.tv_sec = secs;
  tv.tv_usec = (int)(((t - secs) * 1e6) / 1000000);
  return tv;
}
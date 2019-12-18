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
 scalar_t__ system_time () ; 

int uv_uptime(double* uptime) {
  /* system_time() returns time since booting in microseconds */
  *uptime = (double)system_time() / 1000000;
  return 0;
}
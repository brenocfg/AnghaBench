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
struct sysinfo {scalar_t__* loads; } ;

/* Variables and functions */
 scalar_t__ sysinfo (struct sysinfo*) ; 

void uv_loadavg(double avg[3]) {
  struct sysinfo info;

  if (sysinfo(&info) < 0) return;

  avg[0] = (double) info.loads[0] / 65536.0;
  avg[1] = (double) info.loads[1] / 65536.0;
  avg[2] = (double) info.loads[2] / 65536.0;
}
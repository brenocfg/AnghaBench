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
struct sysinfo {double uptime; } ;

/* Variables and functions */
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sysinfo (struct sysinfo*) ; 

int uv_uptime(double* uptime) {
  struct sysinfo info;

  if (sysinfo(&info) < 0)
    return UV__ERR(errno);

  *uptime = info.uptime;
  return 0;
}
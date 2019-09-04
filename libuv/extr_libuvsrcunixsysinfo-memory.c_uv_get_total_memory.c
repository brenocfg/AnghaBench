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
typedef  int uint64_t ;
struct sysinfo {int mem_unit; scalar_t__ totalram; } ;

/* Variables and functions */
 scalar_t__ sysinfo (struct sysinfo*) ; 

uint64_t uv_get_total_memory(void) {
  struct sysinfo info;

  if (sysinfo(&info) == 0)
    return (uint64_t) info.totalram * info.mem_unit;
  return 0;
}
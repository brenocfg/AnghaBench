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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__read_cgroups_uint64 (char*,char*) ; 

uint64_t uv_get_constrained_memory(void) {
  /*
   * This might return 0 if there was a problem getting the memory limit from
   * cgroups. This is OK because a return value of 0 signifies that the memory
   * limit is unknown.
   */
  return uv__read_cgroups_uint64("memory", "memory.limit_in_bytes");
}
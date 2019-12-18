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
typedef  int /*<<< orphan*/  uv_clocktype_t ;
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 unsigned long long TOD_RES ; 
 int /*<<< orphan*/  __stckf (unsigned long long*) ; 

uint64_t uv__hrtime(uv_clocktype_t type) {
  unsigned long long timestamp;
  __stckf(&timestamp);
  /* Convert to nanoseconds */
  return timestamp / TOD_RES;
}
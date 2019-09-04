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
typedef  int /*<<< orphan*/  hc_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline void hc_timer_set (hc_timer_t* a)
{
  #if defined(__APPLE__) && defined(MISSING_CLOCK_GETTIME)
  gettimeofday (a, NULL);
  #else
  clock_gettime (CLOCK_MONOTONIC, a);
  #endif
}
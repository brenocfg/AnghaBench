#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_1__*) ; 
 double hrtime_interval_ ; 

uint64_t uv__hrtime(double scale) {
  LARGE_INTEGER counter;

  /* If the performance interval is zero, there's no support. */
  if (hrtime_interval_ == 0) {
    return 0;
  }

  if (!QueryPerformanceCounter(&counter)) {
    return 0;
  }

  /* Because we have no guarantee about the order of magnitude of the
   * performance counter interval, integer math could cause this computation
   * to overflow. Therefore we resort to floating point math.
   */
  return (uint64_t) ((double) counter.QuadPart * hrtime_interval_ * scale);
}
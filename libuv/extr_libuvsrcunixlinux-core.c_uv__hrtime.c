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
typedef  scalar_t__ uv_clocktype_t ;
typedef  int uint64_t ;
struct timespec {int tv_nsec; int tv_sec; } ;
typedef  int clock_t ;

/* Variables and functions */
 int CLOCK_MONOTONIC ; 
 int CLOCK_MONOTONIC_COARSE ; 
 scalar_t__ UV_CLOCK_FAST ; 
 scalar_t__ clock_getres (int,struct timespec*) ; 
 scalar_t__ clock_gettime (int,struct timespec*) ; 

uint64_t uv__hrtime(uv_clocktype_t type) {
  static clock_t fast_clock_id = -1;
  struct timespec t;
  clock_t clock_id;

  /* Prefer CLOCK_MONOTONIC_COARSE if available but only when it has
   * millisecond granularity or better.  CLOCK_MONOTONIC_COARSE is
   * serviced entirely from the vDSO, whereas CLOCK_MONOTONIC may
   * decide to make a costly system call.
   */
  /* TODO(bnoordhuis) Use CLOCK_MONOTONIC_COARSE for UV_CLOCK_PRECISE
   * when it has microsecond granularity or better (unlikely).
   */
  if (type == UV_CLOCK_FAST && fast_clock_id == -1) {
    if (clock_getres(CLOCK_MONOTONIC_COARSE, &t) == 0 &&
        t.tv_nsec <= 1 * 1000 * 1000) {
      fast_clock_id = CLOCK_MONOTONIC_COARSE;
    } else {
      fast_clock_id = CLOCK_MONOTONIC;
    }
  }

  clock_id = CLOCK_MONOTONIC;
  if (type == UV_CLOCK_FAST)
    clock_id = fast_clock_id;

  if (clock_gettime(clock_id, &t))
    return 0;  /* Not really possible. */

  return t.tv_sec * (uint64_t) 1e9 + t.tv_nsec;
}
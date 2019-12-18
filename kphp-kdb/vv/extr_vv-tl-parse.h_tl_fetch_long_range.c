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
 int /*<<< orphan*/  TL_ERROR_VALUE_NOT_IN_RANGE ; 
 long long tl_fetch_long () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,long long,long long,long long) ; 

__attribute__((used)) static inline long long tl_fetch_long_range (long long min, long long max) {
  long long x = tl_fetch_long ();
  if (x < min || x > max) {
    tl_fetch_set_error_format (TL_ERROR_VALUE_NOT_IN_RANGE, "Expected int64 in range [%lld,%lld], %lld presented", min, max, x);
  }
  return x;
}
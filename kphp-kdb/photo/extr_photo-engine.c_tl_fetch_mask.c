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
 int /*<<< orphan*/  TL_ERROR_BAD_VALUE ; 
 scalar_t__ tl_fetch_error () ; 
 long long tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,long long) ; 

long long tl_fetch_mask (int *force) {
  if (tl_fetch_error()) {
    return 0;
  }
  long long mask = tl_fetch_int();
  if (mask >= 0) {
    *force = (mask >> 29) & 1;
    mask -= (*force << 29);

    if (mask & (1 << 30)) {
      long long mask2 = tl_fetch_int();
      if (mask2 >= 0) {
        return (mask - (1 << 30)) + (mask2 << 29);
      }
    } else {
      return mask;
    }
  }
  tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Wrong mask %lld", mask);
  return 0;
}
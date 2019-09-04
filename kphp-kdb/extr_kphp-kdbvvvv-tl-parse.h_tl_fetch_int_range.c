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
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static inline int tl_fetch_int_range (int min, int max) {
  int x = tl_fetch_int ();
  if (x < min || x > max) {
    tl_fetch_set_error_format (TL_ERROR_VALUE_NOT_IN_RANGE, "Expected int32 in range [%d,%d], %d presented", min, max, x);
  }
  return x;
}
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
 int /*<<< orphan*/  check_rating (double) ; 
 double tl_fetch_double () ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,double) ; 

double tl_fetch_rating (void) {
  if (tl_fetch_error()) {
    return 0;
  }
  double val = tl_fetch_double();
  if (!check_rating (val)) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Wrong rating %.6lf", val);
  }
  return val;
}
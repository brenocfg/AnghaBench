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
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 

int tl_fetch_cat (int set) {
  if (tl_fetch_error ()) {
    return -1;
  }
  int cat = tl_fetch_int ();
  if (set) {
    if (cat <= 0 || cat >= 31) {
      tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Set can be performed on cat in range 1..30. Cat = %d", cat);
      return -1;
    }
  } else {
    if (cat < 0 || cat >= 31) {
      tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Get can be performed on cat in range 0..30. Cat = %d", cat);
      return -1;
    }
  }
  return cat;
}
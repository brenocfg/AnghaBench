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
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*) ; 

int tl_parse_local_id (void) {
  int local_id = tl_fetch_int ();
  if (local_id <= 0) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Local id must be positive integer");
    return -1;
  }
  return local_id;
}
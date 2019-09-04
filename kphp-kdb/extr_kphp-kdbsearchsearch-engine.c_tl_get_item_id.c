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
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long long tl_get_item_id (void) {
  int n = tl_fetch_int ();
  if (n != 1 && n != 2) {
    tl_fetch_set_error ("number of ints in id should be 1 or 2", TL_ERROR_VALUE_NOT_IN_RANGE);
    return -1;
  }
  int owner_id = 0, item_id;
  if (n == 2) {
    owner_id = tl_fetch_int ();
  }
  item_id = tl_fetch_int ();
  if (tl_fetch_error ()) {
    return -1;
  }
  if (item_id <= 0) {
    tl_fetch_set_error ("item_id should be positive", TL_ERROR_VALUE_NOT_IN_RANGE);
    return -1;
  }
  return (n == 2) ? ((long long) item_id << 32) + (unsigned) owner_id : item_id;
}
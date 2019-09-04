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
 int list_id_ints ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int,int) ; 

int tl_fetch_check_list_id_size (void) {
  int x = tl_fetch_int ();
  if (x != list_id_ints) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Wrong number of ints in list_id: should be %d, present %d", list_id_ints, x);
    return -1;
  }
  return 0;
}
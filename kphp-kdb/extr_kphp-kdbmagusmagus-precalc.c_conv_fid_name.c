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
typedef  int /*<<< orphan*/  dl_string ;

/* Variables and functions */
 int /*<<< orphan*/  fid_name_id ; 
 int* map_string_int_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int conv_fid_name (dl_string x, int x_num) {
  int *y = map_string_int_add (&fid_name_id, x);
  if (*y == 0) {
    *y = x_num;
  }
  return *y;
}
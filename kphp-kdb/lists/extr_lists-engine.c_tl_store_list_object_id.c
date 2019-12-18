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
 int object_id_ints ; 
 int /*<<< orphan*/  tl_store_string_data (void*,int) ; 

void tl_store_list_object_id (const int *R, const int *R_end, int mode, int res) {
  const int *Rptr = R;
  int i = 0;
  for (i = 0; i < res; i++) {
    tl_store_string_data ((void *)Rptr, 4 * object_id_ints);
    Rptr += object_id_ints;
  }
}
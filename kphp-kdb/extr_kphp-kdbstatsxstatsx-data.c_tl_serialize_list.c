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
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_raw_data (int*,int) ; 

void tl_serialize_list (int *ptr, int size) {
  if (!ptr) {
    int i;
    for (i = 0; i < size; i++) {
      tl_store_int (0);
    }
  } else {
    tl_store_raw_data (ptr, 4 * size);
  }
}
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

int *unserialize_list2_raw_new (int *ptr, int *data, int num) {
  int x = *(ptr ++);
  int i;
  for (i = 0; i < x; i++) {
    if (*data == num) {
      ptr += 2;
    } else {
      data[2 * (*data) + 1] = *(ptr ++);
      data[2 * (*data) + 2] = *(ptr ++);
      (*data) ++;
    }
  }
  return ptr;
}
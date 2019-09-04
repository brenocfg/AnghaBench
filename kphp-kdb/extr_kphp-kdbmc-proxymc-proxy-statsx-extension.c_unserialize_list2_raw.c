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
 int /*<<< orphan*/  assert (int) ; 

int *unserialize_list2_raw (int *ptr, int *data, int num) {
  int x = *(ptr++);
  assert (x <= num);
  int i, j;
  for (i = 0; i < x; i++) {
    int y = *(ptr++);
    int z = *(ptr++);
    int result = -1;
    for (j = 0; j < num; j ++) if (data[2 * j]  == y) {
      data[2 * j + 1] += z;
      result = j;
      break;
    }
    if (result < 0 && data[2 * (num - 1) + 1] < z) {
      data[2 * (num - 1) + 1] = z;
      data[2 * (num - 1)] = y;
      result = (num - 1);
    }
    while (result > 0) {
      if (data[2 * result + 1] > data[2 * result - 1]) {
        int t;
        t = data[2 * result + 1]; data[2 * result + 1] = data[2 * result - 1]; data[2 * result - 1] = t;
        t = data[2 * result + 0]; data[2 * result + 0] = data[2 * result - 2]; data[2 * result - 2] = t;
        result --;
      } else {
        break;
      }
    }
  }
  return ptr;
}
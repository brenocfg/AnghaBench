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

int in_array (int x, int List[], int len) {
  int a = -1, b = len, c;
  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (List[c] <= x) {
      a = c;
    } else {
      b = c;
    }
  }
  if (a >= 0 && List[a] == x) {
    return a;
  } else {
    return -1;
  }
}
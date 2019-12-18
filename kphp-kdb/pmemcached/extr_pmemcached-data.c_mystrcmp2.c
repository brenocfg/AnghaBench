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

int mystrcmp2 (const char *str1, int l1, const char *str2, int l2, int x) {
  while (x < l1 && x < l2) {
    if (str1[x] < str2[x]) {
      return -x - 1;
    }
    if (str1[x] > str2[x]) {
      return x + 1;
    }
    x++;
  }
  if (l1 < l2) {
    return -x - 1;
  }
  if (l1 > l2) {
    return x + 1;
  }
  return 0;
}
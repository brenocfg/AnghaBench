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

inline int check (long long *v, int vn, long long *u, int un) {
  int i, j;

  for (i = 0, j = 0; i < vn; i++) {
    while (j + 1 < un && u[j] < v[i]) {
      j++;
    }
    if (u[j] != v[i]) {
      return 0;
    }
  }
  return 1;
  /*
  for (i = 0; i < vn; i++) {
    int l = -1, r = un, c;
    while (l + 1 < r) {
      c = (l + r) / 2;
      if (u[c] <= v[i]) {
        l = i;
      } else {
        r = i;
      }
    }
    if (l == -1) {
      return 0;
    }
  }
  return 1;
  */
}
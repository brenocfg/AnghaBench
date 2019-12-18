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

void mg_sort (long long *X, int b) {
  if (b <= 0) { return; }
  int i = 0, j = b;
  long long h = X[b >> 1], t;
  do {
    while (X[i] < h) { i++; }
    while (X[j] > h) { j--; }
    if (i <= j) {
      t = X[i];  X[i++] = X[j];  X[j--] = t;
    }
  } while (i <= j);
  mg_sort (X, j);
  mg_sort (X + i, b - i);
}
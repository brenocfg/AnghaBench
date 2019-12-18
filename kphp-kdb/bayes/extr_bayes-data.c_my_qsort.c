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
 int QL ; 
 int QR ; 
 int rand () ; 

void my_qsort (double *a, int l, int r) {
  if (l >= r || (l > QL && r < QR)) {
    return;
  }

  int i = l, j = r;
  double t, c = a[rand() % (r - l + 1) + l];

  while (i <= j) {
    while (a[i] < c) {
      i++;
    }
    while (a[j] > c) {
      j--;
    }

    if (i <= j) {
      t = a[i];
      a[i] = a[j];
      a[j] = t;
      i++;
      j--;
    }
  }

  my_qsort (a, l, j);
  my_qsort (a, i, r);
}
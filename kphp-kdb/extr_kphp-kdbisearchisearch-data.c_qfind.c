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
typedef  scalar_t__ rating ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int rand () ; 

rating qfind (rating *a, int l, int r, int k) {
  assert (l <= k && k <= r);

  if (l == r) {
    return a[l];
  }

  rating c = a[l + rand() % (r - l + 1)], t;
  int i = l, j = r;

  while (i <= j) {
    while (a[i] < c) {
      i++;
    }
    while (c < a[j]) {
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

  if (k <= j) {
    return qfind (a, l, j, k);
  }
  return qfind (a, j + 1, r, k);
}
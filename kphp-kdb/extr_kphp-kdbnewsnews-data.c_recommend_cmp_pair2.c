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

__attribute__((used)) static int recommend_cmp_pair2 (const void *x, const void *y) {
  const int *a = (const int *) x;
  const int *b = (const int *) y;
  if (a[1] > b[1]) { return -1; }
  if (a[1] < b[1]) { return 1; }
  if (a[0] < b[0]) { return -1; }
  if (a[0] > b[0]) { return 1; }
  return 0;
}
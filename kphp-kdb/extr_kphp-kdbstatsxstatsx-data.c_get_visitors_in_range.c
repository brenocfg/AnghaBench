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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int get_visitors_in_range (int *a, int l, int min, int max) {
  int i, r = 0;
  for (i = 0; i < l; i++) {
    if (max + 1 < a[2 * i + 1]) {
      fprintf (stderr, "max = %d, cur = %d\n", max, a[2 * i + 1]);
    }
    assert (a[2 * i + 1] <= max + 1);
    if (a[2 * i + 1] >= min /*&& a[2 * i + 1] <= max */) {
      r ++;
    }
  }
  return r;
}
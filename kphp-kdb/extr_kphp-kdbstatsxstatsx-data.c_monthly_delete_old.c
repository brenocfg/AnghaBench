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

int monthly_delete_old (int *a1, int l1, int *a2, int l2, int day) {
  int i;
  int r = 0;
  for (i = 0; i < l1; i++) if (a1[2 * i + 1] >= day) {
    assert (r < l2);
    a2[2 * r + 0] = a1[2 * i + 0];
    a2[2 * r + 1] = a1[2 * i + 1];
    r ++;
  }
  return r;
}
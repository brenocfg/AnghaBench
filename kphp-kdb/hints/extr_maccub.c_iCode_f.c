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
 int /*<<< orphan*/  iCode_write (int,unsigned char**,int*,int) ; 

void iCode_f (int *a, int n, int l, int r, unsigned char **res, int *skip) {
  if (n == 0) {
    return;
  }

  int c = n / 2;
  iCode_write (l - a[c] - c, res, skip, l - r - n + 1);
  iCode_f (a, c, l, a[c], res, skip);
  iCode_f (a + c + 1, n - c - 1, a[c] - 1, r, res, skip);
}
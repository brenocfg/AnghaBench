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

void iCode_write (int c, unsigned char **res, int *skip, int r) {
  int k = 0, p = 1;

  if (r == 1) {
    return;
  }

  while (p < r) {
    p += p;
    k++;
  }


  while (k > 8 - *skip) {
    k -= 8 - *skip;
    **res += (unsigned char)((c >> k) << *skip);
    *skip = 0;
    *++(*res) = 0;
  }

  **res += (unsigned char)((c & ((1 << k) - 1)) << (*skip));
  *skip += k;
}
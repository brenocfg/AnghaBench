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

int get_bitno_sparse(int mask, int i) {
  int j, m = 1 << i;
  if (0 == (mask & m) ) return -1;
  for (j = 0;;j++) {
    int w = mask & (mask - 1);
    if (m == (w ^ mask)) return j;
    mask = w;
  }
}
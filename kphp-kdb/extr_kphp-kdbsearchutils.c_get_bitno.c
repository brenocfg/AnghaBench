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
 int popcount_short (int) ; 

int get_bitno(int mask, int i) {
  if (0 == (mask & (1<<i)) ) return -1;
  return popcount_short (mask & ((1 << i) - 1));
}
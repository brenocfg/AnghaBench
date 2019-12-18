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

int cmp_int_inv (const void * _a, const void * _b)
{
  int a = *(int *)_a, b = *(int *)_b;
  if (a < b) {
    return +1;
  } else if (a > b) {
    return -1;
  }
  return 0;
}
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

int cmp_tx (const void *x, const void *y) {
  int a = ((int *)x)[1], b = ((int *)y)[1];
  return a < b ? -1 : a == b ? 0 : +1;
}
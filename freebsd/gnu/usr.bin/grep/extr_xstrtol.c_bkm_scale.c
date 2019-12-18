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
typedef  int __strtol_t ;

/* Variables and functions */

__attribute__((used)) static int
bkm_scale (__strtol_t *x, int scale_factor)
{
  __strtol_t product = *x * scale_factor;
  if (*x != product / scale_factor)
    return 1;
  *x = product;
  return 0;
}
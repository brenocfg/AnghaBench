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
typedef  int /*<<< orphan*/  __strtol_t ;

/* Variables and functions */
 scalar_t__ bkm_scale (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bkm_scale_by_power (__strtol_t *x, int base, int power)
{
  while (power--)
    if (bkm_scale (x, base))
      return 1;

  return 0;
}
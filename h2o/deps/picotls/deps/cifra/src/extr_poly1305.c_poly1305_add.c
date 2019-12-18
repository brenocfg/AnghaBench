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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void poly1305_add(uint32_t h[17],
                         const uint32_t x[17])
{
  uint32_t carry = 0;
  int i;

  for (i = 0; i < 17; i++)
  {
    carry += h[i] + x[i];
    h[i] = carry & 0xff;
    carry >>= 8;
  }
}
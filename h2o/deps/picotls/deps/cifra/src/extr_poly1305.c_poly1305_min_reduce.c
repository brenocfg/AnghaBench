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

__attribute__((used)) static void poly1305_min_reduce(uint32_t x[17])
{
  uint32_t carry = 0;
  int i;
  for (i = 0; i < 16; i++)
  {
    carry += x[i];
    x[i] = carry & 0xff;
    carry >>= 8;
  }

  /* 2 ** 130 - 5 = 0x3fffffffffffffffffffffffffffffffb
   *                  ^
   * So 2 bits of carry are put into top word.
   * Remaining bits get multiplied by 5 and carried back
   * into bottom */
  carry += x[16];
  x[16] = carry & 0x03;
  carry = 5 * (carry >> 2);

  for (i = 0; i < 16; i++)
  {
    carry += x[i];
    x[i] = carry & 0xff;
    carry >>= 8;
  }

  x[16] += carry;
}
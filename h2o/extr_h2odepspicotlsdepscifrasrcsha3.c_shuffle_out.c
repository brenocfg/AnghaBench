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

__attribute__((used)) static inline uint32_t shuffle_out(uint32_t x)
{
  uint32_t t;
  t = (x ^ (x >> 1)) & 0x22222222;  x = x ^ t ^ (t << 1);
  t = (x ^ (x >> 2)) & 0x0c0c0c0c;  x = x ^ t ^ (t << 2);
  t = (x ^ (x >> 4)) & 0x00f000f0;  x = x ^ t ^ (t << 4);
  t = (x ^ (x >> 8)) & 0x0000ff00;  x = x ^ t ^ (t << 8);
  return x;
}
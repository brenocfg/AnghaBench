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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t mask_u8(uint32_t x, uint32_t y)
{
  uint32_t diff = x ^ y;
  uint8_t diff_is_zero = ~diff & (diff - 1);
  return - (diff_is_zero >> 7);
}
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

/* Variables and functions */

__attribute__((used)) static inline void copy_bytes_unaligned(uint8_t *out, const uint8_t *in, size_t len, uint8_t offset)
{
  uint8_t byte_off = offset / 8;
  uint8_t bit_off = offset & 7;
  uint8_t rmask = (1 << bit_off) - 1;
  uint8_t lmask = ~rmask;
  size_t i;

  for (i = 0; i < len; i++)
  {
    out[i] = (in[i + byte_off] << bit_off) & lmask;
    out[i] |= (in[i + byte_off + 1] >> (8 - bit_off)) & rmask;
  }
}
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

__attribute__((used)) static inline void xor_bb(uint8_t *out, const uint8_t *x, const uint8_t *y, size_t len)
{
  size_t i;
  for (i = 0; i < len; i++)
    out[i] = x[i] ^ y[i];
}
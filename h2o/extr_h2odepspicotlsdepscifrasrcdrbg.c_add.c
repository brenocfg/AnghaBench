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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void add(uint8_t *out, size_t nout, const uint8_t *in, size_t nin)
{
  assert(nout >= nin);

  uint16_t carry = 0;
  int oi, ii;

  for (oi = nout - 1, ii = nin - 1;
       oi >= 0;
       ii--, oi--)
  {
    carry += out[oi];
    if (ii >= 0)
      carry += in[ii];
    out[oi] = carry & 0xff;
    carry >>= 8;
  }
}
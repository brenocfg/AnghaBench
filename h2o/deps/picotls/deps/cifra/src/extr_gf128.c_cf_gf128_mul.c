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
typedef  int* cf_gf128 ;

/* Variables and functions */
 int /*<<< orphan*/  cf_gf128_double_le (int*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int* const,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  select_xor128 (int*,int*,int*,int) ; 
 int /*<<< orphan*/  xor_words (int*,int*,int) ; 

void cf_gf128_mul(const cf_gf128 x, const cf_gf128 y, cf_gf128 out)
{
#if CF_TIME_SIDE_CHANNEL_PROTECTION
  cf_gf128 zero = { 0 };
#endif
 
  /* Z_0 = 0^128
   * V_0 = Y */ 
  cf_gf128 Z, V;
  memset(Z, 0, sizeof Z);
  memcpy(V, y, sizeof V);

  int i;
  for (i = 0; i < 128; i++)
  {
    uint32_t word = x[i >> 5];
    uint8_t bit = (word >> (31 - (i & 31))) & 1;

#if CF_TIME_SIDE_CHANNEL_PROTECTION
    select_xor128(Z, zero, V, bit);
#else
    if (bit)
      xor_words(Z, V, 4);
#endif

    cf_gf128_double_le(V, V);
  }

  memcpy(out, Z, sizeof Z);
}
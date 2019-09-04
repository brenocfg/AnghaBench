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
typedef  int /*<<< orphan*/ * bitset_t ;

/* Variables and functions */
 int BITSET_WORDS ; 

__attribute__((used)) static inline void
bitset_mask (bitset_t dest, const bitset_t src)
{
  int bitset_i;
  for (bitset_i = 0; bitset_i < BITSET_WORDS; ++bitset_i)
    dest[bitset_i] &= src[bitset_i];
}
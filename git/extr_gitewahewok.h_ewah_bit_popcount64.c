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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t ewah_bit_popcount64(uint64_t x)
{
	x = (x & 0x5555555555555555ULL) + ((x >>  1) & 0x5555555555555555ULL);
	x = (x & 0x3333333333333333ULL) + ((x >>  2) & 0x3333333333333333ULL);
	x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x >>  4) & 0x0F0F0F0F0F0F0F0FULL);
	return (x * 0x0101010101010101ULL) >> 56;
}
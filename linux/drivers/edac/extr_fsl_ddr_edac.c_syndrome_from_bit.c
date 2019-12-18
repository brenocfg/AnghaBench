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
typedef  unsigned int u8 ;

/* Variables and functions */
 unsigned int* ecc_table ; 

__attribute__((used)) static u8 syndrome_from_bit(unsigned int bit) {
	int i;
	u8 syndrome = 0;

	/*
	 * Cycle through the upper or lower 32-bit portion of each value in
	 * ecc_table depending on if 'bit' is in the upper or lower half of
	 * 64-bit data.
	 */
	for (i = bit < 32; i < 16; i += 2)
		syndrome |= ((ecc_table[i] >> (bit % 32)) & 1) << (i / 2);

	return syndrome;
}
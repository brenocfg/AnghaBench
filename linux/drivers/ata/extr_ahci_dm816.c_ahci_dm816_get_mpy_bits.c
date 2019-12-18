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

/* Variables and functions */
 unsigned long AHCI_DM816_PLL_OUT ; 
 int ARRAY_SIZE (unsigned long*) ; 
 unsigned long* pll_mpy_table ; 

__attribute__((used)) static int ahci_dm816_get_mpy_bits(unsigned long refclk_rate)
{
	unsigned long pll_multiplier;
	int i;

	/*
	 * We need to determine the value of the multiplier (MPY) bits.
	 * In order to include the 8.25 multiplier we need to first divide
	 * the refclk rate by 100.
	 */
	pll_multiplier = AHCI_DM816_PLL_OUT / (refclk_rate / 100);

	for (i = 0; i < ARRAY_SIZE(pll_mpy_table); i++) {
		if (pll_mpy_table[i] == pll_multiplier)
			return i;
	}

	/*
	 * We should have divided evenly - if not, return an invalid
	 * value.
	 */
	return -1;
}
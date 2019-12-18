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
 int RC_BIT_MODEL_TOTAL ; 
 int const RC_BIT_MODEL_TOTAL_BITS ; 
 int RC_BIT_PRICE_SHIFT_BITS ; 
 int RC_MOVE_REDUCING_BITS ; 
 int UINT32_C (int) ; 
 int* rc_prices ; 

__attribute__((used)) static void
init_price_table(void)
{
	for (uint32_t i = (UINT32_C(1) << RC_MOVE_REDUCING_BITS) / 2;
			i < RC_BIT_MODEL_TOTAL;
			i += (UINT32_C(1) << RC_MOVE_REDUCING_BITS)) {
		const uint32_t cycles_bits = RC_BIT_PRICE_SHIFT_BITS;
		uint32_t w = i;
		uint32_t bit_count = 0;

		for (uint32_t j = 0; j < cycles_bits; ++j) {
			w *= w;
			bit_count <<= 1;

			while (w >= (UINT32_C(1) << 16)) {
				w >>= 1;
				++bit_count;
			}
		}

		rc_prices[i >> RC_MOVE_REDUCING_BITS]
				= (RC_BIT_MODEL_TOTAL_BITS << cycles_bits)
				- 15 - bit_count;
	}

	return;
}
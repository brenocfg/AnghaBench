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

__attribute__((used)) static uint32_t mlx5_get_block_order(uint32_t v)
{
	static const uint32_t bits_arr[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
	static const uint32_t shift_arr[] = {1, 2, 4, 8, 16};
	int i;
	uint32_t input_val = v;

	register uint32_t r = 0;/* result of log2(v) will go here */
	for (i = 4; i >= 0; i--) {
		if (v & bits_arr[i]) {
			v >>= shift_arr[i];
			r |= shift_arr[i];
		}
	}
	/* Rounding up if required */
	r += !!(input_val & ((1 << r) - 1));

	return r;
}
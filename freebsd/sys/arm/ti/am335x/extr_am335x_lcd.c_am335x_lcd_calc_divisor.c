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
 int abs (int) ; 

__attribute__((used)) static uint32_t
am335x_lcd_calc_divisor(uint32_t reference, uint32_t freq)
{
	uint32_t div, i;
	uint32_t delta, min_delta;

	min_delta = freq;
	div = 255;

	/* Raster mode case: divisors are in range from 2 to 255 */
	for (i = 2; i < 255; i++) {
		delta = abs(reference/i - freq);
		if (delta < min_delta) {
			div = i;
			min_delta = delta;
		}
	}

	return (div);
}
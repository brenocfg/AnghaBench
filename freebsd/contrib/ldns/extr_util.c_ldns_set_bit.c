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

void
ldns_set_bit(uint8_t *byte, int bit_nr, bool value)
{
	/*
	 * The bits are counted from right to left, so bit #0 is the
	 * right most bit.
	 */
	if (bit_nr >= 0 && bit_nr < 8) {
		if (value) {
			*byte = *byte | (0x01 << bit_nr);
		} else {
			*byte = *byte & ~(0x01 << bit_nr);
		}
	}
}
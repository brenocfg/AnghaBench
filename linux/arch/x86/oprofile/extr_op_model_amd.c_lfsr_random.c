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

__attribute__((used)) static unsigned int lfsr_random(void)
{
	static unsigned int lfsr_value = 0xF00D;
	unsigned int bit;

	/* Compute next bit to shift in */
	bit = ((lfsr_value >> 0) ^
	       (lfsr_value >> 2) ^
	       (lfsr_value >> 3) ^
	       (lfsr_value >> 5)) & 0x0001;

	/* Advance to next register value */
	lfsr_value = (lfsr_value >> 1) | (bit << 15);

	return lfsr_value;
}
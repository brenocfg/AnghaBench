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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */

__attribute__((used)) static uint32_t
gen_bitmask(int msb, int lsb)
{
	uint32_t mask;

	if (msb == sizeof(mask) * 8 - 1)
		mask = ~0;
	else
		mask = (1U << (msb + 1)) - 1;

	if (lsb > 0)
		mask &= ~((1U << lsb) - 1);

	return (mask);
}